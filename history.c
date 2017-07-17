#include "header.h"

/**
 * history_list - initializes linked list of history from history file in $HOME
 * @arginv: arguments inventory
 *
 * Return: head (pointer to first node of linked list of environ variables)
 */
history_t *history_list(arg_inventory_t *arginv)
{
	history_t *head;
	char *file, *buffer;
	int fd;
	size_t iterations = 1, charcount = 0, i = 0;

	head = NULL;
	file = arginv->history_file;
	fd = open(file, O_RDONLY);
	buffer = safe_malloc(sizeof(char) * BUFSIZE);
	if (fd == -1 || buffer == NULL)
	{
		free(buffer);
		return (head);
	}
	while (TRUE)
	{
		i = read(fd, (buffer + charcount), BUFSIZE);
		if (i <= 0)
			break;
		charcount += i;
		if (i % BUFSIZE == 0)
		{
			iterations++;
			buffer = _realloc(buffer, charcount, (BUFSIZE * iterations));
		}
		else
			break;
	}
	close(fd);
	if (charcount == 0)
	{
		free(buffer);
		return (head);
	}
	head = init_history(head, buffer);
	return (head);
}

/**
 * init_history - initializes history using history file converted to buffer
 * @head: head of linked list of history commands
 * @buffer: old history backup converted to string
 *
 * Return: head (pointer to first node of linked list of environ variables)
 */
history_t *init_history(history_t *head, char *buffer)
{
	int marker, sublen, j, i = 0;
	char *temp;

	while (buffer[i] != '\0')
	{
		marker = i;
		sublen = 0;
		while (buffer[i] != '\n')
			sublen++, i++;
		temp = safe_malloc(sizeof(char) * (sublen + 2));
		j = 0;
		while (j <= sublen)
		{
			temp[j] = buffer[marker];
			j++, marker++;
		}
		add_node_history(&head, temp);
		i++;
		free(temp);
	}
	free(buffer);
	return (head);
}

/**
 * add_node_history - adds new node to end of linked list of input history
 * @head: head of history linked list
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
	new_node->number = 0;
	if (!*head)
		*head = new_node;
	else
	{
		temp = *head;

		while (temp->next)
		{
			temp = temp->next;
			i++;
		}
		if (i > 4095)
		{
			free_history(*head);
			*head = new_node;
			return (new_node);
		}
		new_node->number = i;
		temp->next = new_node;
	}

	return (new_node);
}

/**
 * file_history - converts history to string to file in history file
 * @arginv: arguments inventory
 *
 * Return: 0 success, 1 failure
 */
int file_history(arg_inventory_t *arginv)
{
	char *history_text;

	history_text = history_to_string(arginv->history);
	trunc_text_to_file(arginv->history_file, history_text);

	free(history_text);

	return (0);
}

/**
 * history_to_string - converts history linked list to string
 * @head: head of linked list of history
 *
 * Return: linked list converted to string
 */
char *history_to_string(history_t *head)
{
	history_t *temp = head;
	char *string;
	unsigned int size = 0;

	while (temp)
	{
		size += _strlen(temp->command);
		temp = temp->next;
	}

	string = safe_malloc(sizeof(char) * (size + 1));

	temp = head;
	while (temp)
	{
		_strncat(string, temp->command, _strlen(temp->command));
		temp = temp->next;
	}

	return (string);
}
