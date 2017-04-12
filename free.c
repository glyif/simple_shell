#include "header.h"

/**
 * freeall - function to free all allocated memory
 * @arginv: args inventory
 *
 * Return: 0 on success, 1 on failure
 */
int freeall(arg_inventory_t *arginv)
{
	free_environ(arginv->envlist);
   	free_history(arginv->history);
	free(arginv->input_commands);

	return (EXT_SUCCESS);
}

/**
 * free_environ - function to free all allocated memory
 * @head - head of custom _environ
 *
 * Return: 0 on success, 1 on failure
 */
int free_environ(env_t *head)
{
	env_t *temp = head;

	while (head)
	{
		temp = temp->next;
		free(head->var);
		free(head->val);
		free(head);
		head = temp;
	}

	return (EXT_SUCCESS);
}

/**
 * free_history - function to free all allocated memory
 * @head: history linked list
 *
 * Return: 0 on success, 1 on failure
 */
int free_history(history_t *head)
{
	history_t *temp = head;

	while (head)
	{
		temp = temp->next;
		free(head->command);
		free(head);
		head = temp;
	}

	return (EXT_SUCCESS);
}
