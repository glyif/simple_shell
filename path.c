#include "header.h"
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
			_strncpy(path, tmp->var, len);
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
