#include "header.h"

/**
 * tokenize - tokenizes command string
 * @tokens: tokens_t struct containing initial string and array of strings
 * @string: command string
 *
 * Return: 0, or exits with error
 */
int tokenize(tokens_t *tokens, const char *string)
{
	unsigned int length, string_idx, data_idx, tokens_idx;
	unsigned int skip_next, skip_quote;
	unsigned int is_token;
	unsigned int i;
	char *data;
	char symbol;

	length = _strlen(string);
	if (length == 0)
		length = 1;
	init_tokens(tokens, length);
	data = safe_malloc((length * 2 + 1) * sizeof(char));
	string_idx = 0; data_idx = 0; tokens_idx = 0; skip_next = 0;
	skip_quote = 0; is_token = 0;

	while (string[string_idx] != '\0' && string[string_idx] != '#')
	{
		symbol = string[string_idx];
		string_idx++;

		if (!is_token && _isspace(symbol))
			continue;
		if (!is_token && !_isspace(symbol) && (symbol != ';'))
		{
			tokens->tokens[tokens_idx].str = data + data_idx;
			tokens_idx++;
			is_token = 1;
		}
		if (is_token && _isspace(symbol) && !skip_next && !skip_quote)
		{
			data[data_idx] = '\0';
			data_idx++;
			is_token = 0;
			continue;
		}
		if ((symbol == ';') && !skip_next && !skip_quote)
		{
			if (is_token)
			{
				data[data_idx] = '\0';
				data_idx++;
			}
			tokens->tokens[tokens_idx].str = data + data_idx;
			tokens_idx++;
			data[data_idx] = ';';
			data[data_idx + 1] = '\0';
			data_idx += 2;
			is_token = 0;
			continue;
		}
		if ((symbol == '\"') && !skip_next)
		{
			skip_quote = !skip_quote;
			continue;
		}
		if ((symbol == '\\') && !skip_next)
		{
			skip_next = 1;
			continue;
		}
		skip_next = 0;
		data[data_idx] = symbol;
		data_idx++;
	}

	data[data_idx] = '\0';
	tokens->tokensN = tokens_idx;

	token_classify(tokens);
	delete_dups(tokens);

	if (tokens->tokensN && tokens->tokens[tokens->tokensN - 1].id == TOKEN_SEMICOLON)
		tokens->tokensN--;
	for (i = 0; i < tokens->tokensN; i++)
		tokens->tokens[i].str = _strdup((char *)tokens->tokens[i].str);

	return (0);
}
