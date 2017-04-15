#include "header.h"
/**
 * alias_list - builtin func to set alias list
 *
 * Return: 0 on success
 */
alias_t *alias_list(void)
{
	alias_t *head;

	head = NULL;

	return (head);
}

/**
 * _alias - builtin func to set alias
 * @arginv - arguments inventory
 *
 * Return: 0 on success
 */
int _alias(arg_inventory_t *arginv)
{
	char *input, **combo, **commands;

	commands = (char**)arginv->commands;

	if (commands[1] == NULL)
	{
		perror("alias: missing parameters.");
		return (-1);
	}

	input = commands[1];

	combo = separate_string(input);

	add_node_alias(&arginv->alias, combo[0], combo[1]);

	write_alias(arginv->alias);

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

/**
 * add_node_alias - builtin func to set alias
 * @head - head of alias list
 * @alias: alias ot add
 * @command: actual command equivalent to alias
 *
 * Return: 0 on success
 */

alias_t *add_node_alias(alias_t **head, char *alias, char *command)
{
	alias_t *new_node, *temp;

	new_node = malloc(sizeof(alias_t));
	if (new_node == NULL)
		return (NULL);

	new_node->alias = _strdup(alias);
	new_node->command = _strdup(command);
	new_node->next = NULL;

	if (!*head)
		*head = new_node;
	else
	{
		temp = *head;

		while (temp->next)
			temp = temp->next;

		temp->next = new_node;
	}

	return (new_node);
}

/**
 * write_alias - function to write alias list to stdout for testing
 * @head - head of alias list
 *
 * Return: chars written
 */
int write_alias(alias_t *head)
{
	int i = 0;
	alias_t *temp = head;

	while (temp)
	{
		_putchar('[');
		write(STDOUT_FILENO, temp->alias, _strlen(temp->alias));
		write(STDOUT_FILENO, "] = [", 5);
		write(STDOUT_FILENO, temp->command, _strlen(temp->command));
		_putchar(']');
		_putchar('\n');

		temp = temp->next;
		i++;
	}

	return (i);
}
