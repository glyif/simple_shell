#include "header.h"

/**
 * _alias - builtin func to set alias
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _alias(arg_inventory_t *arginv)
{
	char *input, **combo, **commands;

	commands = (char **)arginv->commands;

	if (commands[1] == NULL)
	{
		write_alias(arginv->alias);
		return (EXT_SUCCESS);
	}
	else if (commands[2] != NULL)
	{
		_perror("alias: too many arguments.\n");
		return (-1);
	}

	input = commands[1];

	combo = separate_string(input);

	if (modify_node_alias(&arginv->alias, combo[0], combo[1]) == EXT_FAILURE)
		add_node_alias(&arginv->alias, combo[0], combo[1]);

	free(combo[0]);
	free(combo[1]);
	free(combo);
	return (EXT_SUCCESS);
}

/**
 * _unalias - builtin func to unset alias
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _unalias(arg_inventory_t *arginv)
{
	char **commands;

	commands = (char **)arginv->commands;

	if (commands[1] == NULL)
	{
		_perror("unalias: missing arguments.\n");
		return (-1);
	}

	if (commands[2] != NULL)
	{
		_perror("unalias: too many arguments.\n");
		return (-1);
	}

	if (remove_node_alias(&arginv->alias, commands[1]) == EXT_SUCCESS)
		return (EXT_SUCCESS);

	return (EXT_FAILURE);
}

/**
 * the_help - prints help commands info based on the other input argument
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int the_help(arg_inventory_t *arginv)
{
	char **commands;
	int i = 0, retval = 127;
	bins_t bins[] = {
		{"exit", h_exit}, {"arsine", h_arsine}, {"env", h_env},
		{"setenv", h_setenv}, {"unsetenv", h_unsetenv},
		{"history", h_history}, {"cd", h_cd}, {"alias", h_alias},
		{"help", h_help},
		{NULL, NULL}
	};


	commands = (char **)arginv->commands;
	if (commands[2] != NULL)
	{
		_perror("help: too many input commands.\n");
		return (retval);
	}

	while (bins[i].function != NULL)
	{
		if (_strcmp(bins[i].function, commands[1]) == 0)
		{
			bins[i].help();
			retval = EXT_SUCCESS;
			break;
		}
		i++;
	}

	return (retval);
}

/**
 * the_exit - exit status to exit
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int the_exit(arg_inventory_t *arginv)
{
	char **commands;
	int es;

	commands = (char **)arginv->commands;
	if (commands[1] == NULL)
		arginv->exit = 1;
	else if (is_uint(commands[1]))
	{
		es = _atoi(commands[1]);
		arginv->exit = 1;
		arginv->exit_status = es;
	}
	else
		_perror("exit: Illegal number\n");

	return (EXT_SUCCESS);
}
