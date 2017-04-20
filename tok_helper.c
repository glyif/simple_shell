#include "header.h"
#include "token_types.h"

/**
 * delete_dups - deletes duplicate ; from data
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
 * @tokens - tokens_t struct
 */
void token_classify(tokens_t *tokens)
{
	unsigned int i, j;

	for (i = 0; i < tokens->tokensN; i++)
	{
		tokens->tokens[i].id = TOKEN_STRING;

		for (j = 0; j < sizeof(token_names) / sizeof(token_names[0]); j++)
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
