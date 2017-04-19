#include "header.h"

/**
 * init_tokens - initializes token struct
 * @tokens: tokens struct to initialize
 * @length: length to malloc for
 */
void init_tokens(tokens_t *tokens, int length)
{
	tokens->tokens = safe_malloc(length * sizeof(token_t));

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
	return (token_id == TOKEN_REWRITE || token_id == TOKEN_APPEND ||
			token_id == TOKEN_CAT);
}

/**
 * delete_tokens - freeing tokens
 * @tokens: tokens_t struct with tokens
 * Return: 0
 */
int delete_tokens(tokens_t *tokens)
{
	unsigned int i;

	for (i = 0; i < tokens->tokensN; i++)
		free(tokens->tokens[i].str);

	free(tokens->tokens);
	tokens->tokens = NULL;
	tokens->tokensN = 0;

	return (0);
}
