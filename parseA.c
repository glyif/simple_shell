#include "header.h"

/**
 * parse_error - prints parser error
 * @near: where the issue is at
 *
 * Return: 1 because of error
 */
int parse_error(token_t *near)
{
	if (near)
		_perror("Parse error near\n");
	else
		_perror("Parse error\n");

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
ptree_t *parse_expr(unsigned int *ntoken, tokens_t *tokens, ptree_t *lhs,
					int min_prec)
{
	int lookahead, op;
	ptree_t *rhs, *new;

	lookahead = *ntoken;
	while (*ntoken < tokens->tokensN && tokens->tokens[lookahead].prec >=
		   min_prec)
	{
		op = *ntoken;
		*ntoken = *ntoken + 1;
		rhs = ptree_new_string_node(lhs, tokens, ntoken);
		if (rhs == NULL)
		{
			if (*ntoken < tokens->tokensN || tokens->tokens[op].id !=
				TOKEN_BACKGROUND)
			{
				parse_error(&tokens->tokens[*ntoken]);
				return (NULL);
			}
		}
		else if (*ntoken < tokens->tokensN)
		{
			lookahead = *ntoken;
			while (*ntoken < tokens->tokensN && tokens->tokens[lookahead].id !=
				   TOKEN_STRING && tokens->tokens[lookahead].prec >
				   tokens->tokens[op].prec)
			{
				rhs = parse_expr(ntoken, tokens, rhs,
								 tokens->tokens[lookahead].prec);
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
		return (parse_error(NULL));

	ptree = ptree_new_string_node(NULL, tokens, &cur_token);

	if (!ptree)
		return (parse_error(tokens->tokens + 0));

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
