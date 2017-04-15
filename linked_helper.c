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
	{
		*head = new_node;
	}
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
 * @new_var: variable to modify
 * @new_val: new string to be modified to found node
 *
 * Return: pointer to new node or NULL if fail
 */
int modify_node_env(env_t **head, char *new_var, char *new_val)
{
	env_t *temp;

	temp = *head;

	while (temp)
	{
		if (_strcmp(temp->var, new_var) == 0)
		{
			free(temp->val);
			temp->val = _strdup(new_val);

			return (EXT_SUCCESS);
		}
		temp = temp->next;
	}

	return (EXT_FAILURE);
}

/**
 * remove_node_env - removes node from linked list
 * @head: beginning of linked list
 * @var: var of node to be removed from linked list
 *
 * Return: pointer to new node or NULL
 */
int remove_node_env(env_t **head, char *var)
{
	env_t *copy_head = *head, *temp = *head;

	while (temp)
	{
		if (_strcmp(temp->var, var) == 0)
		{
			while (copy_head->next != temp)
				copy_head = copy_head->next;

			copy_head->next = temp->next;

			free(temp->var);
			free(temp->val);
			free(temp);

			return (EXT_SUCCESS);
		}
		temp = temp->next;
	}

	return (EXT_FAILURE);
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
		variable = separate_string(environ[i]);
		if (add_node_env(&head, variable[0], variable[1]) == NULL)
			return (NULL);
		free(variable[0]);
		free(variable[1]);
		free(variable);
	}

	return (head);
}

/**
 * separate_string - separates string at first '='
 * @string: one string from environ or alias input
 *
 * Return: array of 2 strings
 */
char **separate_string(char *string)
{
	char **result, *left, *right;
	int i, j, lenleft = 0, lenright = 0;

	while (string[lenleft] != '=')
		lenleft++;
	left = safe_malloc(sizeof(char) * lenleft + 1);

	for (i = 0; i < lenleft; i++)
		left[i] = string[i];

	i = lenleft + 1;

	while (string[i] != '\0')
		lenright++, i++;
	right = safe_malloc(sizeof(char) * lenright + 1);

	for (i = lenleft + 1, j = 0; j < lenright; i++, j++)
		right[j] = string[i];

	result = safe_malloc(sizeof(char *) * 3);
	result[0] = left, result[1] = right;

	return (result);
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

/**
 * fetch_node - fetches a node of a given var
 * @head: head of list
 * @var: value to match of the node to fetch
 *
 * Return: fetched node or head
 */
env_t *fetch_node(env_t *head, char *var)
{
    env_t *tmp;
    tmp = head;

    while (tmp->next != NULL)
    {
        if (_strcmp(tmp->var, var) == 0)
            return (tmp);
        else
            tmp = tmp->next;
    }

    return (head);
}
