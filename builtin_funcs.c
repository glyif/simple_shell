#include "header.h"

/**
 * _exit - exits daVinci
 * @arginv - arguments inventory
 *
 * Return: 0 on success
 */
int the_exit(arg_inventory_t *arginv)
{
	(void)arginv;

	exit(EXT_SUCCESS);
}

/**
 * _env - exits daVinci
 * @arginv - arguments inventory
 *
 * Return: 0 on success
 */
int _env(arg_inventory_t *arginv)
{
	env_t *envlist = arginv->envlist;

	print_list(envlist);

	return(EXT_SUCCESS);
}

/**
 * _setenv - sets new environmental variable
 * @arginv - arguments inventory
 *
 * Return: 0 on success
 */
int _setenv(arg_inventory_t *arginv)
{
	int len1, len2, lenval;
	char **commands, *var, *val, *new_value;
	env_t *envlist = arginv->envlist;

	commands = arginv->tokens->tokens;
	var = commands[1];
	val = commands[2];

	len1 = _strlen(var);
	len2 = _strlen(val);

	lenval = len1 + len2 + 2;
	new_value = safe_malloc(lenval * sizeof(char));

	_strncat(new_value, var, len1);
	_strncat(new_value, "=", 1);
	_strncat(new_value, val, len2);

	if (modify_node(&envlist, var, new_value) == NULL)
		add_node_end(&envlist, new_value);

	return(EXT_SUCCESS);
}

/**
 * _monalisa - prints mona lisa ascii art
 * @arginv - arguments inventory
 *
 * Return: 0 on success
 */
int _monalisa(arg_inventory_t *arginv)
{
	(void)arginv;

	if (!read_textfile("monalisa.txt", 3808))
		write(STDOUT_FILENO, "Simplicity is the ultimate sophistication\n", 42);

	return (EXT_SUCCESS);
}
