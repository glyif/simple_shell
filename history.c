#include "header.h"

/**
 * history_list - initializes linked list
 *
 * Return: head (pointer to first node of linked list of environ variables)
 */
history_t *history_list(void)
{
	history_t *head;
	head = NULL;

	return (head);
}

/**
 * add_node_history - adds new node to end of linked list of input history
 * @arginv: head of history linked list
 * @command: new command
 *
 * Return: pointer to new node
 */
history_t *add_node_history(history_t **head, char *command)
{
	history_t *new_node, *temp;
	unsigned int i = 1;

	new_node = malloc(sizeof(history_t));
	if (new_node == NULL)
		return (NULL);

	new_node->command = _strdup(command);
	new_node->next = NULL;

	if (!*head)
	{
		new_node->number = 0;
		*head = new_node;
	}
	else
	{
		temp = *head;

		while (temp->next)
		{
			temp = temp->next;
			i++;
		}

		new_node->number = i;
		temp->next = new_node;
	}

	return (new_node);
}
