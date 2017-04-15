#include "header.h"

/**
 * locate_path - sorts through list of environs to find find custom PATH
 * @path: copies path
 * @envlist: environmental variables list
 */
int locate_path(char *path, env_t *envlist)
{
	env_t *tmp;
	tmp = envlist;

	while(tmp)
	{
		if (_strcmp(tmp->var, "PATH") == 0)
		{
			_strcpy(path, tmp->val);
			return (1);
		}

		tmp = tmp->next;
	}

	return (1);
}

int cat_path(char **search_path, char *cmd)
{
	int i, fd, len;
	char *new;

	new = safe_malloc(BUFSIZE);

	for (i = 0; search_path[i] != NULL; i++)
	{
		new = _strcpy(new, search_path[i]);
		len = _strlen(new);
		new[len] = '/';

		new = _strncat(new, cmd, _strlen(cmd));
		fd = access(new, F_OK);
		if (fd == 0)
		{
			_strcpy(cmd, new);
			return (0);
		}
		else
		{
			new = mem_reset(new, BUFSIZE);
		}
	}

	return (-1);
}
