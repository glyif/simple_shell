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

	file_history(arginv);

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

/**
 * file_history - converts history to string to file
 * @arginv: arguments inventory
 *
 * Return: 0 success, 1 failure
 */
int file_history(arg_inventory_t *arginv)
{
	char *file = ".simple_shell_history";
	char *history_text;

	history_text = history_to_string(arginv->history);

	append_text_to_file(file, history_text);

	free(history_text);

	return (0);
}

/**
 * history_to_string - converts history to string
 * @history: linked list of history
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
