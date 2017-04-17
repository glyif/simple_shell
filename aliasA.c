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
 * add_node_alias - builtin func to set alias
 * @head: head of alias list
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
 * modify_node_alias - checks to see if node exists, and modifies it if so.
 * @head: beginning of linked list
 * @new_var: variable to modify
 * @new_val: new string to be modified to found node
 *
 * Return: pointer to new node or NULL if fail
 */
int modify_node_alias(alias_t **head, char *new_var, char *new_val)
{
	alias_t *temp;

	temp = *head;

	while (temp)
	{
		if (_strcmp(temp->alias, new_var) == 0)
		{
			free(temp->command);
			temp->command = _strdup(new_val);

			return (EXT_SUCCESS);
		}
		temp = temp->next;
	}

	return (EXT_FAILURE);
}


/**
 * remove_node_alias - removes node from linked list
 * @head: beginning of linked list
 * @var: var of node to be removed from linked list
 *
 * Return: pointer to new node or NULL
 */
int remove_node_alias(alias_t **head, char *var)
{
	alias_t *copy_head = *head, *temp = *head;

	if (head == NULL)
		return (EXT_FAILURE);
	copy_head = NULL;
	while (temp)
	{
		if (_strcmp(temp->alias, var) == 0)
		{
			if (copy_head)
				copy_head->next = temp->next;
			else
				*head = temp->next;

			free(temp->alias);
			free(temp->command);
			free(temp);

			return (EXT_SUCCESS);
		}
		copy_head = temp;
		temp = temp->next;
	}

	return (EXT_FAILURE);
}


/**
 * write_alias - function to write alias list to stdout for testing
 * @head: head of alias list
 *
 * Return: chars written
 */
int write_alias(alias_t *head)
{
	int i = 0;
	alias_t *temp = head;

	while (temp)
	{
		write(STDOUT_FILENO, temp->alias, _strlen(temp->alias));
	    write(STDOUT_FILENO, "=\"", 2);
		write(STDOUT_FILENO, temp->command, _strlen(temp->command));
	    write(STDOUT_FILENO, "\"\n", 2);

		temp = temp->next;
		i++;

	}

	return (i);
}
