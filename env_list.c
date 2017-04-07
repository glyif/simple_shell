#include "header.h"

/**
 * env_node - adds new env node to end of linked list of environ variables
 * @head: address of pointer to first node of linked list
 * @str: new environmental variable to added to linked list
 *
 * Return: pointer to new node with new environ variable
 */
env_t *env_node(env_t **head, char *str)
{
	env_t *new;
	env_t *tmp;

	new = malloc(sizeof(env_t));
	if (new == NULL)
		return (NULL);

	new->var = _strdup(str);
	new->next = NULL;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (new);
}

/**
 * env_list - creates a linked list of all environ variables
 * Description: this function calls env_node() to add each environ variable,
 * (from extern char** environ) one at a time to the linked list of environ
 * variables.
 *
 * Return: head (pointer to first node of linked list of environ variables)
 */
env_t *env_list(void)
{
	int i;
	env_t *head;

	head = NULL;

	for (i = 0; environ[i] != NULL; i++)
		if (env_node(&head, environ[i]) == NULL)
			return (NULL);

	return (head);
}
