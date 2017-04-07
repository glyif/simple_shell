#include "header.h"

/**
 * link_count - counts number of nodes in linked list
 * @envp: pointer to head of linked list
 * 
 * Return: number of nodes
 */
unsigned int link_count(env_t *envp)
{
	env_t *tmp;
	unsigned int count;

	tmp = envp;
	count = 0;

	while (tmp != NULL)
	{
		tmp = tmp->next;
		count++;
	}

	return (count);
}

/**
 * zelda_to_ganondorf - converts linked list to double pointer
 * @env_p: head pointer to head of list
 *
 * Return: array of pointers pointing to strings
 */
char **zelda_to_ganondorf(env_t *envp)
{
	int i;
	unsigned int count, len;
	char **ganondorf;
	env_t *tmp;

	count = link_count(envp);
	ganondorf = malloc(sizeof(char *) * (count + 1));

	tmp = envp;
	i = 0;
	while (tmp != NULL)
	{
		len = _strlen(tmp->var);
		ganondorf[i] = safe_malloc(sizeof(char *) * (len + 1));
		_strncpy(ganondorf[i], tmp->var, len);
		tmp = tmp->next;
	}
	
	ganondorf[i] = NULL;

	return (ganondorf);
}
