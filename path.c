#include "header.h"

/**
 * locate_path - sorts through list of environs to find find custom PATH
 * @path: copies path
 */
int locate_path(char *path, env_t *envlist)
{
	env_t *tmp;
	int len;
	tmp = envlist;

	while(tmp->next != NULL)
	{
		if (path_match(tmp->var, "PATH=") != 0)
		{
			len = _strlen(tmp->var);
			_strncpy(path, (tmp->var + 5), len);
			return (1);
		}

		tmp = tmp->next;
	}

	return (1);
}

int path_match(char *path, char *str)
{
	int i;

	if (path == NULL || str == NULL)
		return (0);

	i = 0;

	while (path[i] == str[i])
	{
		if (path[i] == '\0' || str[i] == '\0')
			return (1);

		i++;
	}

	if (path[i] == '\0' || str[i] == '\0')
		return (1);

	return (0);
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
		fd = open(new, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
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
