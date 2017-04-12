#include "header.h"

/**
 * link_count - counts number of nodes in linked list
 * @head: pointer to head of linked list
 *
 * Return: number of nodes
 */
unsigned int link_count(env_t *head)
{
	env_t *tmp;
	unsigned int count;

	tmp = head;
	count = 0;

	while (tmp != NULL)
	{
		tmp = tmp->next;
		count++;
	}

	return (count);
}

/**
 * add_node_env - adds new node to end of linked list
 * @head: beginning of linked list
 * @str: new string to be added to linked list
 *
 * Return: pointer to new node
 */
env_t *add_node_env(env_t **head, char *str)
{
	env_t *new_node, *temp;

	new_node = malloc(sizeof(env_t));
	if (new_node == NULL)
		return (NULL);

	new_node->var = _strdup(str);
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
 * modify_node_env - checks to see if node exists, and modifies it if so.
 * @head: beginning of linked list
 * @val: value to modify
 * @str: new string to be modified to found node
 *
 * Return: pointer to new node or NULL if fail
 */
env_t *modify_node_env(env_t **head, char *val, char *str)
{
	env_t *temp_node;

	temp_node = *head;

	while (temp_node)
	{
		if (_strncmp(temp_node->var, val, _strlen(val)) == 0)
		{
			free(temp_node->var);
			temp_node->var = _strdup(str);
			return (temp_node);
		}
		temp_node = temp_node->next;
	}

	return (NULL);
}

/**
 * print_list - prints all elements of linked list
 * @head: head of linked list to print
 *
 * Return: number of nodes printed
 */
size_t print_list(env_t *head)
{
	unsigned int i = 0;

	while (head)
	{
		_puts(head->var);
		head = head->next;
		i++;
	}

	return (i);
}

/**
 * zelda_to_ganondorf - converts linked list to double pointer
 * @head: head pointer to head of linked list
 *
 * Return: array of pointers, pointing to strings
 */
char **zelda_to_ganondorf(env_t *head)
{
	int i;
	unsigned int count, len;
	char **ganondorf;
	env_t *tmp;

	count = link_count(head);
	ganondorf = malloc(sizeof(char *) * (count + 1));

	tmp = head;
	i = 0;
	while (tmp != NULL)
	{
		len = _strlen(tmp->var);
		ganondorf[i] = safe_malloc(sizeof(char *) * (len + 1));
		_strncpy(ganondorf[i], tmp->var, len);
		tmp = tmp->next;
		i++;
	}
	ganondorf[i] = NULL;

	return (ganondorf);
}
