#include "header.h"

/**
 * _getpid - gets the pid and starts a new child precess
 *
 * Return: returns the pid of new child process
 */
int _getpid(void)
{
	int pid;

	pid = fork();

	return (pid);
}

/**
 * bash_replace - replaces env vars
 * @arginv: arg inventory
 * @index: index of token_t struct array
 */
void bash_replace(arg_inventory_t *arginv, int index)
{
	unsigned int j;
	env_t *node;
	tokens_t t = arginv->tokens;

	for (j = 0; j < _strlen(t.tokens[index].str); j++)
		if (t.tokens[index].str[j] == '$' && t.tokens[index].str[j + 1] != '\0')
			switch (t.tokens[index].str[j + 1])
			{
				case '$':
					replace_str((char **)&t.tokens[index].str,
						int_to_str(_getpid()), j, j + 1, 1);
					break;
				case '?':
					replace_str((char **)&t.tokens[index].str,
						int_to_str(arginv->exit_status), j,
						j + 1, 1);
					break;
				case '!':
						replace_str((char **)&t.tokens[index].str,
						(arginv->last_bg_pid == -1) ? "" :
						int_to_str(arginv->last_bg_pid), j,
						j + 1, 1);
					break;
				case '0':
					replace_str((char **)&t.tokens[index].str, "hsh", j,
						j + 1, 0);
						break;
				default:
					node = fetch_node(arginv->envlist,
							(char *)&t.tokens[index].str[j + 1]);
					replace_str((char **)&t.tokens[index].str,
							(node == NULL) ? "" : node->val, j,
							_strlen(t.tokens[index].str) - 1, 0);
					}
				else if (t.tokens[index].str[j] == '~' && j == 0)
				{
					node = fetch_node(arginv->envlist, "HOME");
					replace_str((char **)&t.tokens[index].str, node->val, j, j, 0);
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
	unsigned int i;
	tokens_t t = arginv->tokens;

	for (i = 0; i < t.tokensN; i++)
		if (t.tokens[i].id == TOKEN_STRING)
			bash_replace(arginv, i);
}

/**
 * expand_alias - expand the alias found in the command strings
 *
 * @arginv: args inventory
 * Return: int
 */
int expand_alias(arg_inventory_t *arginv)
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
				(char *)arginv->commands[i];
		}

		for (i = 0; i < cmd_tokens.tokensN; i++)
			commands[i] = _strdup((char *)cmd_tokens.tokens[i].str);
		free(arginv->commands[0]);
		free(arginv->commands);
		commands[count + cmd_tokens.tokensN - 1] = NULL;
		count = cmd_tokens.tokensN;
		arginv->commands = commands;
		delete_tokens(&cmd_tokens);
		return (count - 1);
	}
	return (0);
}
