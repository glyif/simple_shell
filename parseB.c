#include "header.h"

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
	tokens_t t = arginv->tokens;

	for (i = 0; i < t.tokensN; i++)
		if (t.tokens[i].id == TOKEN_STRING)
		{
			for (j = 0; j < _strlen(t.tokens[i].str); j++)
				if (t.tokens[i].str[j] == '$')
					switch (t.tokens[i].str[j + 1])
					{
						case '$':
							replace_str((char **)&t.tokens[i].str,
										int_to_str(getpid()), j, j + 1, 1);
							break;
						case '?':
							replace_str((char **)&t.tokens[i].str,
										int_to_str(arginv->last_exit_code), j,
										j + 1, 1);
							break;
						case '!':
							replace_str((char **)&t.tokens[i].str,
										(arginv->last_bg_pid == -1) ? "" :
										int_to_str(arginv->last_bg_pid), j,
										j + 1, 1);
							break;
						case '0':
							replace_str((char **)&t.tokens[i].str, "hsh", j,
										j + 1, 0);
							break;
						default:
							node = fetch_node(arginv->envlist,
											  (char *)&t.tokens[i].str[j + 1]);
							replace_str((char **)&t.tokens[i].str,
										(node == NULL) ? "" : node->val, j,
										_strlen(t.tokens[i].str) - 1, 0);
					}
				else if (t.tokens[i].str[j] == '~' && j == 0)
				{
					node = fetch_node(arginv->envlist, "HOME");
					replace_str((char **)&t.tokens[i].str, node->val, j, j, 0);
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
			commands[i + cmd_tokens.tokensN - 1] =
				(char *)_strdup((char *)arginv->commands[i]);
		}

		for (i = 0; i < cmd_tokens.tokensN; i++)
		{
			commands[i] = _strdup((char *)cmd_tokens.tokens[i].str);
		}
		arginv->commands = (const char **)commands;
		delete_tokens(&cmd_tokens);
	}
}
