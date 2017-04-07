#include "header.h"

/**
 * env_node - adds env node to end
 * @head: address of the head
 * @str: var to be stored
 */
void env_node(env_t **head, char *str)
{
	env_t *new;
	env_t *tmp;

	new = malloc(sizeof(env_t));
	
	new->var = _strdup(str);
	new->next = NULL;

	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/**
 * env_list - creates a linked list of all envion variables
 * 
 * Return: head pointer of the created environ list
 */
env_t *env_list(void)
{
	int i;
	env_t *head;

	head = NULL;

	for (i = 0; environ[i] != NULL; i++)
		env_node(&head, environ[i]);

	return (head);
}
