#include "header.h"

/**
 * _env - writes env to stdout
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _env(arg_inventory_t *arginv)
{
	env_t *envlist = arginv->envlist;

	print_list(envlist);

	return (EXT_SUCCESS);
}

/**
 * _history - writes history to stdout
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _history(arg_inventory_t *arginv)
{
	history_t *historylist = arginv->history;

	write_history(historylist);

	return (EXT_SUCCESS);
}

/**
 * _setenv - sets new environmental variable
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _setenv(arg_inventory_t *arginv)
{
	char **commands, *new_var, *new_val;
	env_t *envlist = arginv->envlist;

	commands = (char **)arginv->commands;

	if (commands[1] == NULL || commands[2] == NULL)
	{
		perror("setenv: missing parameters.");
		return (-1);
	}

	if (commands[3] != NULL)
	{
		perror("setenv: missing value.");
		return (-1);
	}

	new_var = commands[1];
	new_val = commands[2];

	if (modify_node_env(&envlist, new_var, new_val) == EXT_FAILURE)
	{
		add_node_env(&envlist, new_var, new_val);
	}

	return (EXT_SUCCESS);
}

/**
 * _unsetenv - sets new environmental variable
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _unsetenv(arg_inventory_t *arginv)
{
	char **commands;
	env_t *envlist = arginv->envlist;

	commands = (char **)arginv->commands;

	if (commands[1] == NULL)
	{
		perror("unsetenv: missing parameters.");
		return (-1);
	}

	if (commands[2] != NULL)
	{
		perror("unsetenv: too many input commands.");
		return (-1);
	}

	if (remove_node_env(&envlist, commands[1]))
		return (EXT_FAILURE);

	return (EXT_SUCCESS);
}

/**
 * _monalisa - prints mona lisa ascii art
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _monalisa(arg_inventory_t *arginv)
{
	(void)arginv;

	write(STDOUT_FILENO, "Simplicity is the ultimate sophistication\n", 42);

	return (EXT_SUCCESS);
}

/**
 * the_help - prints mona lisa ascii art
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int the_help(arg_inventory_t *arginv)
{
	char **commands;
	int i = 0;
	bins_t bins[] = {
		{"exit", h_exit}, {"monalisa", h_monalisa}, {"env", h_env},
		{"setenv", h_setenv}, {"unsetenv", h_unsetenv},
		{"history", h_history}, {"cd", h_cd}, {"alias", h_alias},
		{"help", h_help},
		{NULL, NULL}
	};


	commands = (char **)arginv->commands;
	if (commands[2] != NULL)
	{
		perror("help: too many input commands.");
		return (-1);
	}

	while (bins[i].function != NULL)
	{
		if (_strcmp(bins[i].function, commands[1]) == 0)
		{
			bins[i].help();
			break;
		}
		i++;
	}

	return (EXT_SUCCESS);
}
