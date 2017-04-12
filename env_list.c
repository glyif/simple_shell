#include "header.h"

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
		if (add_node_env(&head, environ[i]) == NULL)
			return (NULL);

	return (head);
}
