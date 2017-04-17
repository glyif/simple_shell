#include "header.h"

/**
 * init_tokens - initializes token struct
 * @tokens: tokens struct to initialize
 * @length: length to malloc for
 */
void init_tokens(tokens_t *tokens, int length)
{
	/* For the extreme case, such as 'a;a;a;a;a;a', we'll need to allocate twice as much memory for data + 1 byte for terminator */
	/* Maximum amount of tokens is the same as length */
	tokens->data = safe_malloc((length * 2 + 1) * sizeof(char));
	tokens->tokens = safe_malloc(length * sizeof(token_t));

	if (!tokens->data || !tokens->tokens)
	{
		perror("Unable to allocate memory for tokens");
		exit(1); /* This is a critical error */
	}

	/* Initialize the rest of the structure */
	tokens->tokensN = 0;
}

/**
 * is_redirection - checks if token id is a redirection
 * @token_id: tokenid
 *
 * Return: 1 if yes , 0 if no
 */
int is_redirection(int token_id)
{
    return (token_id == TOKEN_REWRITE || token_id == TOKEN_APPEND || token_id == TOKEN_CAT);
}

/**
 * delete_tokens - freeing tokens
 * @tokens: tokens_t struct with tokens
 * Return: 0
 */
int delete_tokens(tokens_t *tokens)
{
	free(tokens->data);
	tokens->data = NULL;

	free(tokens->tokens);
	tokens->tokens = NULL;
	tokens->tokensN = 0;

	return (0);
}

/**
 * dump_tokens - prints tokens for debugging
 * @tokens: tokens_t struct
 *
 * Return: 0
 */
int dump_tokens(tokens_t *tokens)
{
	unsigned int i;

	printf("There are %u tokens in token structure: ======================\n", tokens->tokensN);

	for (i = 0; i < tokens->tokensN; i++)
		printf("%14s token \"%s\"\n", dump_get_token_descr(tokens->tokens[i].id), tokens->tokens[i].str);

	return (0);
}

/**
 * dump_get_token_descr - prints token description for debugging)
 * @token_id: macro token
 *
 * Return: token_descr or error message
 */
const char *dump_get_token_descr(int token_id)
{
	unsigned int i;

	token_types token_names[] = {
		{ TOKEN_SEMICOLON,  ";",  "semicolon",  1 },
		{ TOKEN_BACKGROUND, "&",  "background", 1 },
		{ TOKEN_AND,        "&&", "and",        2 },
		{ TOKEN_OR,         "||", "or",         2 },
		{ TOKEN_PIPE,       "|",  "pipe",       3 },
		{ TOKEN_REWRITE,    ">",  "rewrite",    4 },
		{ TOKEN_APPEND,     ">>", "append",     4 },
		{ TOKEN_CAT,        "<",  "cat",        4 }
	};

	if (token_id == TOKEN_STRING)
		return ("string");

	for (i = 0; i < sizeof(token_names) / sizeof(token_names[0]); i++)
		if (token_names[i].token_id == token_id)
			return (token_names[i].token_descr);

	return ("Done messed up A-Aron");
}
