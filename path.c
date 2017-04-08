#include "header.h"
int locate_path(char *path, env_t *envlist)
{
	env_t *tmp;
	int len;
	tmp = envlist;

	while(tmp->next != NULL)
	{
		if (path_match(tmp->var) == EXT_SUCCESS)
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
	char *p_env;

	p_env = "PATH=";

	if (path == NULL)
		return (EXT_FAILURE);

	while (path[i] == p_env[i])
	{
		if (path[i] == '\0' || p_env[i] == '\0')
			return (EXT_SUCCESS);
		i++;
	}
	
	return (EXT_FAILURE);
}
