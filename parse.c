#include "header.h"

/**
 * parse_error - prints parser error
 * @error: error to print
 * @near: where the issue is at
 *
 * Return: 1 because of error
 */
int parse_error(const char *error, token_t *near)
{
	if (near)
		fprintf(stderr, "Parse error near \"%s\": %s\n", near->str, error);
	else
		fprintf(stderr, "Parse error: %s\n", error);

	return (1);
}

/**
 * parse_expr - operator precedence parser
 * @ntoken: token number;
 * @tokens: tokens_t struct;
 * @lhs: left hand side;
 * @min_prec: minimum precedent
 *
 * Return: pointer to built tree
 */
ptree_t *parse_expr(unsigned int *ntoken, tokens_t *tokens, ptree_t *lhs, int min_prec)
{
	int lookahead, op;
	ptree_t *rhs, *new;

	lookahead = *ntoken;

	while (*ntoken < tokens->tokensN && tokens->tokens[lookahead].prec >= min_prec)
	{
		op = *ntoken;
		*ntoken = *ntoken + 1;

		rhs = ptree_new_string_node(lhs, tokens, ntoken);

		if (rhs == NULL)
		{
			if (*ntoken < tokens->tokensN || tokens->tokens[op].id != TOKEN_BACKGROUND)
			{
				parse_error("Line starts with operator, expected command", &tokens->tokens[*ntoken]);
				return (NULL);
			}
		}
		else if (*ntoken < tokens->tokensN)
		{
			lookahead = *ntoken;

			while (*ntoken < tokens->tokensN && tokens->tokens[lookahead].id != TOKEN_STRING && tokens->tokens[lookahead].prec > tokens->tokens[op].prec)
			{
				rhs = parse_expr(ntoken, tokens, rhs, tokens->tokens[lookahead].prec);

				if (rhs == NULL)
					return (NULL);

				lookahead = *ntoken;
			}
		}

		new = ptree_new_node(NULL);
		new->token_id = tokens->tokens[op].id;
		new->left = lhs;
		new->right = rhs;
		lhs = new;
	}

	return (lhs);
}

/**
 * parse - main funciton that creates the entire parse tree from the tokenizer
 * @parser: parser_t struct
 * @tokens: tokens_t struct
 *
 * Return: 0
 */
int parse(parser_t *parser, tokens_t *tokens)
{
	ptree_t *ptree;
	unsigned int cur_token = 0;

	parser->tree = NULL;

	if (tokens->tokensN == 0)
		return (parse_error("Nothing to parse", NULL));

	ptree = ptree_new_string_node(NULL, tokens, &cur_token);

	if (!ptree)
		return (parse_error("Line starts with operator, expected command", tokens->tokens + 0));

	parser->tree = ptree;

	parser->tree = parse_expr(&cur_token, tokens, ptree, 0);

	if (parser->tree == NULL)
		return (1);

	return (0);
}

/**
 * delete_parser - frees parser struct
 * @parser: parser struct
 *
 * Return: 0;
 */
int delete_parser(parser_t *parser)
{
	if (!parser->tree)
		return (0);

	delete_ptree(parser->tree);
	parser->tree = NULL;

	return (0);
}

/**
 * replace_str - replace part of string by another
 *
 * @old_str: string that will be modified
 * @new_str: string to be used as replacement
 * @i: starting position to replace in old_str
 * @j: ending position to replace in old_str
 * @flg: indicates if new_str should be freed
 *
 */
void replace_str(char **old_str, char *new_str, int i, int j, int flg)
{
	*old_str = _str_replace(*old_str, i, j, new_str);
	if (flg)
	{
		if (new_str[0])
			free(new_str);
	}
}

/**
 * expand_bash_vars - expand all variables found in the arginv strings
 *
 * @arginv: args inventory
 *
 */
void expand_bash_vars(arg_inventory_t *arginv)
{
	unsigned int i, j;
	env_t *node;

	for (i = 0; i < arginv->tokens.tokensN; i++)
		if (arginv->tokens.tokens[i].id == TOKEN_STRING)
		{
			for (j = 0; j < _strlen(arginv->tokens.tokens[i].str); j++)
				if (arginv->tokens.tokens[i].str[j] == '$')
					switch (arginv->tokens.tokens[i].str[j + 1])
					{
						case '$':
							replace_str((char **)&arginv->tokens.tokens[i].str, int_to_str(getpid()), j, j + 1, 1);
							break;
						case '?':
							replace_str((char **)&arginv->tokens.tokens[i].str, int_to_str(arginv->last_exit_code), j, j + 1, 1);
							break;
						case '!':
							replace_str((char **)&arginv->tokens.tokens[i].str, (arginv->last_bg_pid == -1) ? "" : int_to_str(arginv->last_bg_pid), j, j + 1, 1);
							break;
						case '0':
							replace_str((char **)&arginv->tokens.tokens[i].str, "hsh", j, j + 1, 0);
							break;
						default:
							node = fetch_node(arginv->envlist, (char *)&arginv->tokens.tokens[i].str[j + 1]);
							replace_str((char **)&arginv->tokens.tokens[i].str, (node == NULL) ? "" : node->val, j, _strlen(arginv->tokens.tokens[i].str) - 1, 0);
					}
				else if (arginv->tokens.tokens[i].str[j] == '~' && j == 0)
				{
					node = fetch_node(arginv->envlist, "HOME");
					replace_str((char **)&arginv->tokens.tokens[i].str, node->val, j, j, 0);
				}
		}
}

/**
 * expand_alias - expand the alias found in the command strings
 *
 * @arginv: args inventory
 *
 */
void expand_alias(arg_inventory_t *arginv)
{
	alias_t *node;
	tokens_t cmd_tokens;
	unsigned int i;
	char **commands;
	unsigned int count = 0;

	node = fetch_node_alias(arginv->alias, (char *)arginv->commands[0]);

	if (node != NULL)
	{
		tokenize(&cmd_tokens, node->command);
		count = 0;
		while (arginv->commands[count] != NULL)
		{
			count++;
		}
		commands = safe_malloc((count + cmd_tokens.tokensN) * sizeof(char *));
		for (i = count - 1; i >= 1; i--)
		{
			commands[i + cmd_tokens.tokensN - 1] = (char *)_strdup((char *)arginv->commands[i]);
		}

		for (i = 0; i < cmd_tokens.tokensN; i++)
		{
			commands[i] = _strdup((char *)cmd_tokens.tokens[i].str);
		}
		arginv->commands = (const char **)commands;
		delete_tokens(&cmd_tokens);
	}
}
