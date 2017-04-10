#include "header.h"
#include "pa_struct.h"

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
 * parse - main funciton that creates the entire parse tree from the tokenizer
 * @parser: parser_t struct
 * @tokens: tokens_t struct
 *
 * Return: 0
 */
int parse(parser_t *parser, tokens_t *tokens)
{
	int nxt_token;
	int prev_token;
	ptree_t *ptree;
	unsigned int cur_token;

	/* Setup the root of the MEGA Parse Tree */
	parser->tree = NULL;

	/* is there a token? */
	if (tokens->tokensN == 0)
		return (parse_error("Nothing to parse", NULL));

	/* Next, check that the very first token is token_string, not anything else */
	/* This is super important! because a command should never start with anything but a string */
	cur_token = 0;
	ptree = ptree_insert_string(NULL, tokens, &cur_token);

	if (!ptree)
		return (parse_error("Line starts with operator, expected command", tokens->tokens + 0));

	/* setup parser tree to ptree struct */
	parser->tree = ptree;

	while (cur_token < tokens->tokensN)
	{

		nxt_token = tokens->tokens[cur_token].id;
		prev_token = ptree->token_id;

		if (nxt_token == TOKEN_STRING)
		{
			if (prev_token == TOKEN_STRING)
				return (parse_error("Set of strings follows set of strings", tokens->tokens + cur_token));
			else
				ptree = ptree_insert_string(ptree, tokens, &cur_token);
		}
		else if (nxt_token == TOKEN_BACKGROUND)
		{
			ptree = ptree_insert_token_right(ptree, tokens, &cur_token);
		}
		else
		{
			if (prev_token == TOKEN_STRING)
				ptree = ptree_emplace_token(ptree, tokens, &cur_token);
			else
				return (parse_error("Two non-string tokens follow each other", tokens->tokens + cur_token));
		}
	}

	/* updated tree to root of tree */
	parser->tree = ptree_get_root(ptree);

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

	delete_ptree(ptree_get_root(parser->tree));
	parser->tree = NULL;

	return (0);
}
