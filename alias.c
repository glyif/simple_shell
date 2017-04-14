#include "header.h"

/**
 * _alias - builtin func to set alias
 * @arginv - arguments inventory
 *
 * Return: 0 on success
 */
int _alias(arg_inventory_t *arginv)
{
	(void)arginv;

	return (EXT_SUCCESS);
}

/**
 * _unalias - builtin func to unset alias
 * @arginv - arguments inventory
 *
 * Return: 0 on success
 */
int _unalias(arg_inventory_t *arginv)
{
	(void)arginv;

	return (0);
}
