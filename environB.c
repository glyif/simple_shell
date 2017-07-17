#include "header.h"

/**
 * add_node_env - adds new node to end of linked list
 * @head: beginning of linked list
 * @var: variable to be added
 * @val: value to be added
 *
 * Return: pointer to new node
 */
env_t *add_node_env(env_t **head, char *var, char *val)
{
	env_t *new_node, *temp;

	new_node = safe_malloc(sizeof(env_t));

	new_node->var = _strdup(var);
	new_node->val = _strdup(val);
	new_node->next = NULL;

	if (!*head)
	{
		*head = new_node;
	}
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
 * modify_node_env - checks to see if node exists, and modifies it if so.
 * @head: beginning of linked list
 * @new_var: variable to modify
 * @new_val: new string to be modified to found node
 *
 * Return: pointer to new node or NULL if fail
 */
int modify_node_env(env_t **head, char *new_var, char *new_val)
{
	env_t *temp;

	temp = *head;

	while (temp)
	{
		if (_strcmp(temp->var, new_var) == 0)
		{
			free(temp->val);
			temp->val = _strdup(new_val);

			return (EXT_SUCCESS);
		}
		temp = temp->next;
	}

	return (EXT_FAILURE);
}

/**
 * remove_node_env - removes node from linked list
 * @head: beginning of linked list
 * @var: var of node to be removed from linked list
 *
 * Return: pointer to new node or NULL
 */
int remove_node_env(env_t **head, char *var)
{
	env_t *copy_head = *head, *temp = *head;

	if (head == NULL)
		return (EXT_FAILURE);
	copy_head = NULL;
	while (temp)
	{
		if (_strcmp(temp->var, var) == 0)
		{
			if (copy_head)
				copy_head->next = temp->next;
			else
				*head = temp->next;

			free(temp->var);
			free(temp->val);
			free(temp);

			return (EXT_SUCCESS);
		}
		copy_head = temp;
		temp = temp->next;
	}

	return (EXT_FAILURE);
}

/**
 * fetch_node - fetches a node of a given var
 * @head: head of list
 * @var: value to match of the node to fetch
 *
 * Return: fetched node or head
 */
env_t *fetch_node(env_t *head, char *var)
{
	env_t *tmp;

	tmp = head;

	while (tmp != NULL)
	{
		if (_strcmp(tmp->var, var) == 0)
			return (tmp);

		tmp = tmp->next;
	}

	return (NULL);
}
