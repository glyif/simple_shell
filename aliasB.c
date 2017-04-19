#include "header.h"

/**
 * save_alias - saves alias definitions to  file
 * @arginv: arguments inventory
 *
 * Return: 0 success, 1 failure
 */
int save_alias(arg_inventory_t *arginv)
{
	alias_t *tmp = arginv->alias;
	char *name = "/.simple_shell_alias";
	char *file, *home, *buffer;
	env_t *home_node;
	int lenhome, fd, lenname = _strlen(name);

	home_node = fetch_node(arginv->envlist, "HOME");
	home = home_node->val;
	lenhome = _strlen(home);

	file = safe_malloc(sizeof(char) * (_strlen(home) + lenname + 1));
	file = _strncat(file, home, lenhome);
	file = _strncat(file, name, lenname);

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	close(fd);

	while (tmp)
	{
		buffer = (char *)safe_malloc(_strlen(tmp->alias) + _strlen(tmp->command)
									 + 4);
		_strcpy(buffer, tmp->alias);
		_strcat(buffer, ":");
		_strcat(buffer, tmp->command);
		_strcat(buffer, "\n");
		append_text_to_file(file, buffer);
		tmp = tmp->next;
		free(buffer);
	}

	free(file);
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
	ssize_t count;
	size_t sz = BUFSIZE;
	char *name = "/.simple_shell_alias";
	char *file, *home, *buffer, *val;
	env_t *home_node;
	int lenhome, fd, lenname = _strlen(name);

	home_node = fetch_node(arginv->envlist, "HOME");
	home = home_node->val;
	lenhome = _strlen(home);

	file = safe_malloc(sizeof(char) * (_strlen(home) + lenname + 1));
	file = _strncat(file, home, lenhome);
	file = _strncat(file, name, lenname);

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(file);
		return (1);
	}
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
	free(file);
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
