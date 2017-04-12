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
env_t *add_node_env(env_t **head, char *var, char *val)
{
	env_t *new_node, *temp;

	new_node = malloc(sizeof(env_t));
	if (new_node == NULL)
		return (NULL);

	new_node->var = _strdup(var);
	new_node->val = _strdup(val);
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
env_t *modify_node_env(env_t **head, char *new_var, char *new_val)
{
	env_t *temp_node;

	temp_node = *head;

	while (temp_node)
	{
		if (sp_strncmp(temp_node->var, new_var, _strlen(new_var)) == 0)
		{
			free(temp_node->var);
			temp_node->var = _strdup(new_var);
			free(temp_node->val);
			temp_node->val = _strdup(new_val);
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
	char **_environ;

	_environ = zelda_to_ganondorf(head);

	while (_environ[i])
	{
		_puts(environ[i]);
		i++;
	}

	return (i);
}


/**
 * env_list - creates a linked list of all environ variables
 *
 * Return: head (pointer to first node of linked list of environ variables)
 */
env_t *env_list(void)
{
	int i;
	env_t *head;
	char **variable;
	head = NULL;

	for (i = 0; environ[i] != NULL; i++)
	{
		variable = separate_env(environ[i]);
		if (add_node_env(&head, variable[0], variable[1]) == NULL)
			return (NULL);
		free(variable[0]);
		free(variable[1]);
		free(variable);
	}

	return (head);
}

/**
 * separate_env - separates environ element to var and val
 * @string: one element of environ list
 * Return: void
 */
char **separate_env(char *string)
{
	char **variable, *var, *val;
	int i, j, lenvar = 0, lenval = 0;

	while (string[lenvar] != '=')
		lenvar++;
	var = safe_malloc(sizeof(char) * lenvar + 1);
	for (i = 0; i < lenvar; i++)
		var[i] = string[i];

	i = lenvar + 1;

	while (string[i] != '\0')
		lenval++, i++;
	val = safe_malloc(sizeof(char) * lenval + 1);
	for (i = lenvar + 1, j = 0; j < lenval; i++, j++)
		val[j] = string[i];

	variable = safe_malloc(sizeof(char *) * 2);
	variable[0] = var, variable[1] = val;

	return (variable);
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
	unsigned int count, len1, len2, lennew;
	char **ganondorf, *var, *val, *new_val;
	env_t *tmp;

	count = link_count(head);
	ganondorf = malloc(sizeof(char *) * (count + 1));

	tmp = head;
	i = 0;
	while (tmp != NULL)
	{
		var = tmp->var;
		val = tmp->val;
		len1 = _strlen(var);
		len2 = _strlen(val);

		lennew = len1 + len2 + 2;
		new_val = safe_malloc(lennew * sizeof(char));

		_strncat(new_val, var, len1);
		_strncat(new_val, "=", 1);
		_strncat(new_val, val, len2);
		ganondorf[i] = new_val;
		tmp = tmp->next;
		i++;
	}
	ganondorf[i] = NULL;

	return (ganondorf);
}
