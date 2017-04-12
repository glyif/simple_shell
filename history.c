#include "header.h"

/**
 * add_node_history - adds new node to end of linked list of input history
 * @arginv: arguments inventory
 *
 * Return: pointer to new node
 */
history_t *add_node_history(history_t **head, char *command)
{
	history_t *new_node, *temp;
	unsigned int i = 0;

	new_node = safe_malloc(sizeof(history_t));
	if (new_node == NULL)
		return (NULL);

	new_node->number = i;
	new_node->command = _strdup(command);
	new_node->next = NULL;

	if (!*head)
	{
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

		temp->next = new_node;
		new_node->number = i;
	}

	return (new_node);
}

/**
 * write_history - writes all elemets of history to file
 * @head: head of linked list to print
 *
 * Return: number of nodes printed
 */
unsigned int write_history(history_t *head)
{
	unsigned int i = 0;
	printf("his\n");
	while (head)
	{
		_puts(head->command);
		head = head->next;
		i++;
	}

	return (i);
}
