#include "header.h"
/**
 * alias_list - builtin func to set alias list
 *
 * Return: 0 on success
 */
alias_t *alias_list(void)
{
	alias_t *head;

	head = NULL;

	return (head);
}

/**
 * _alias - builtin func to set alias
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _alias(arg_inventory_t *arginv)
{
	char *input, **combo, **commands;

	commands = (char **)arginv->commands;

	if (commands[1] == NULL)
	{
		write_alias(arginv->alias);
		return (EXT_SUCCESS);
	}
	else if (commands[2] != NULL)
	{
		perror("alias: too many arguments.");
		return (-1);
	}

	input = commands[1];

	combo = separate_string(input);

	if (modify_node_alias(&arginv->alias, combo[0], combo[1]) == EXT_FAILURE)
	{
		add_node_alias(&arginv->alias, combo[0], combo[1]);
	}
	return (EXT_SUCCESS);
}

/**
 * _unalias - builtin func to unset alias
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _unalias(arg_inventory_t *arginv)
{
	char **commands;

	commands = (char **)arginv->commands;

	if (commands[1] == NULL)
	{
		perror("unalias: missing arguments.");
		return (-1);
	}

	if (commands[2] != NULL)
	{
		perror("unalias: too many arguments.");
		return (-1);
	}

	if (remove_node_alias(&arginv->alias, commands[1]) == EXT_SUCCESS)
		return (EXT_SUCCESS);

	return (EXT_FAILURE);
}

/**
 * add_node_alias - builtin func to set alias
 * @head: head of alias list
 * @alias: alias ot add
 * @command: actual command equivalent to alias
 *
 * Return: 0 on success
 */

alias_t *add_node_alias(alias_t **head, char *alias, char *command)
{
	alias_t *new_node, *temp;

	new_node = malloc(sizeof(alias_t));
	if (new_node == NULL)
		return (NULL);

	new_node->alias = _strdup(alias);
	new_node->command = _strdup(command);
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
 * modify_node_alias - checks to see if node exists, and modifies it if so.
 * @head: beginning of linked list
 * @new_var: variable to modify
 * @new_val: new string to be modified to found node
 *
 * Return: pointer to new node or NULL if fail
 */
int modify_node_alias(alias_t **head, char *new_var, char *new_val)
{
	alias_t *temp;

	temp = *head;

	while (temp)
	{
		if (_strcmp(temp->alias, new_var) == 0)
		{
			free(temp->command);
			temp->command = _strdup(new_val);

			return (EXT_SUCCESS);
		}
		temp = temp->next;
	}

	return (EXT_FAILURE);
}


/**
 * remove_node_alias - removes node from linked list
 * @head: beginning of linked list
 * @var: var of node to be removed from linked list
 *
 * Return: pointer to new node or NULL
 */
int remove_node_alias(alias_t **head, char *var)
{
	alias_t *copy_head = *head, *temp = *head;

	if (head == NULL)
		return (EXT_FAILURE);
	copy_head = NULL;
	while (temp)
	{
		if (_strcmp(temp->alias, var) == 0)
		{
			if (copy_head)
				copy_head->next = temp->next;
			else
				*head = temp->next;

			free(temp->alias);
			free(temp->command);
			free(temp);

			return (EXT_SUCCESS);
		}
		copy_head = temp;
		temp = temp->next;
	}

	return (EXT_FAILURE);
}


/**
 * write_alias - function to write alias list to stdout for testing
 * @head: head of alias list
 *
 * Return: chars written
 */
int write_alias(alias_t *head)
{
	int i = 0;
	alias_t *temp = head;

	while (temp)
	{
		write(STDOUT_FILENO, temp->alias, _strlen(temp->alias));
	    write(STDOUT_FILENO, "=\"", 2);
		write(STDOUT_FILENO, temp->command, _strlen(temp->command));
	    write(STDOUT_FILENO, "\"\n", 2);

		temp = temp->next;
		i++;

	}

	return (i);
}

/**
 * save_alias - saves alias definitions to  file
 * @arginv: arguments inventory
 *
 * Return: 0 success, 1 failure
 */
int save_alias(arg_inventory_t *arginv)
{
	char *file = ".simple_shell_alias";
	char *buffer;
	alias_t *tmp = arginv->alias;
	int fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	close(fd);

	while (tmp)
	{
		buffer = (char *)safe_malloc(_strlen(tmp->alias) + _strlen(tmp->alias) + 4);
		_strcpy(buffer, tmp->alias);
		_strcat(buffer, ":");
		_strcat(buffer, tmp->command);
		_strcat(buffer, "\n");
		append_text_to_file(file, buffer);
		tmp = tmp->next;
	}

	return (0);
}

/**
 * load_alias - loads alias definitions from file
 * @arginv: arguments inventory
 *
 * Return: 0 success, 1 failure
 */
int load_alias(arg_inventory_t *arginv)
{
	char *file = ".simple_shell_alias";
	char *buffer, *val;
	int fd;
	ssize_t count;
	size_t sz = BUFSIZE;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);

	buffer = (char *)safe_malloc(sz);

	while ((count = _readline(fd, &buffer, &sz)) != 0)
	{
		while (buffer[count - 1] == '\n')
			buffer[count - 1] = '\0';

		val = buffer;

		while (*val && *val != ':')
			val++;

		if (!*val)
			break;

		*(val++) = '\0';

		add_node_alias(&arginv->alias, buffer, val);
	}
	free(buffer);
	close(fd);
	return (0);
}

/**
 * fetch_node_alias - fetches a node of a given alias
 * @head: head of list
 * @var: alias to match of the node to fetch
 *
 * Return: fetched node or NULL
 */
alias_t *fetch_node_alias(alias_t *head, char *var)
{
	alias_t *tmp;

	tmp = head;

	while (tmp != NULL)
	{
		if (_strcmp(tmp->alias, var) == 0)
			return (tmp);

		tmp = tmp->next;
	}

	return (NULL);
}

