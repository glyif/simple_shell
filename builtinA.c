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
	char **commands;

	commands = (char **)arginv->commands;

	if (commands[1] != NULL)
	{
		_perror("env: No such file or directory\n");
		return (-1);
	}

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
		_perror("setenv: missing parameters.\n");
		return (-1);
	}

	if (commands[3] != NULL)
	{
		_perror("setenv: missing value.\n");
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
		_perror("unsetenv: missing parameters.\n");
		return (-1);
	}

	if (commands[2] != NULL)
	{
		_perror("unsetenv: too many input commands.\n");
		return (-1);
	}

	if (remove_node_env(&envlist, commands[1]))
		return (EXT_FAILURE);

	return (EXT_SUCCESS);
}

/**
 * _arsine - prints mona lisa ascii art
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _arsine(arg_inventory_t *arginv)
{
	(void)arginv;

	_puts("AsH3 special thanks to Walter White");

	return (EXT_SUCCESS);
}
