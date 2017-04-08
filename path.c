#include "header.h"
int locate_path(char *path, env_t *envlist)
{
	env_t *tmp;
	int len;
	tmp = envlist;

	while(tmp->next != NULL)
	{
		if (path_match(tmp->var) != 0)
		{
			len = _strlen(tmp->var);
			_strncpy(path, tmp->var, len);
			return (0);
		}

		tmp = tmp->next;
	}

	return (1);
}

int path_match(char *path)
{
	int i;
	char *p_string;

	p_string = "PATH=";

	if (path == NULL)
		return (0);

	while (path[i] == p_string[i])
	{
		if (path[i] == '\0' || p_string[i] == '\0')
			return (1);
		i++;
	}

	if (path[i] == '\0' || p_string[i] == '\0')
		return (1);
	
	return (0);
}
