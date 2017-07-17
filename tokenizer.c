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

/**
 * delete_dups - deletes duplicate semi-colons from data
 * @tokens: tokens_t struct
 */
void delete_dups(tokens_t *tokens)
{
	unsigned int i, tokens_to_move;

	for (i = 0; i + 1 < tokens->tokensN;)
	{
		if ((tokens->tokens[i].id == tokens->tokens[i + 1].id) &&
				(tokens->tokens[i].id == TOKEN_SEMICOLON))
		{
			tokens_to_move = tokens->tokensN - i - 1;
			_memmove(tokens->tokens + i, tokens->tokens + i + 1,
					tokens_to_move * sizeof(token_t));

			tokens->tokensN--;
		}
		else
		{
			i++;
		}
	}
}

/**
 * token_classify - classifies the tokens
 * @tokens: tokens_t struct
 */
void token_classify(tokens_t *tokens)
{
	unsigned int i;
	int j;

	token_types token_names[] = {
		{ TOKEN_SEMICOLON,  ";",  "semicolon",  1 },
		{ TOKEN_BACKGROUND, "&",  "background", 1 },
		{ TOKEN_AND,        "&&", "and",        2 },
		{ TOKEN_OR,         "||", "or",         2 },
		{ TOKEN_PIPE,       "|",  "pipe",       3 },
		{ TOKEN_REWRITE,    ">",  "rewrite",    4 },
		{ TOKEN_APPEND,     ">>", "append",     4 },
		{ TOKEN_CAT,        "<",  "cat",        4 },
		{ 9, '\0', '\0', 9}
	};

	for (i = 0; i < tokens->tokensN; i++)
	{
		tokens->tokens[i].id = TOKEN_STRING;

		for (j = 0; token_names[j].token_id != 9; j++)
		{
			if (_strcmp(token_names[j].token_str, tokens->tokens[i].str) == 0)
			{
				tokens->tokens[i].id = token_names[j].token_id;
				tokens->tokens[i].prec = token_names[j].precedence;
				break;
			}
		}
	}
}
