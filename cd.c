#include "header.h"

/**
 * yellow_brick_road - assembles path to cd into
 * @commands: array of pointer pointg to commands
 * @envlist: head of env linked list
 *
 * Return: full filepath
 */
char *yellow_brick_road(char **commands, env_t *envlist)
{
	env_t *fetched_home;
	env_t *fetched_old;
	int tilda;
	int hyphen;
	char *path;

	path = malloc(1024);

	fetched_home = fetch_node(envlist, "HOME");
	fetched_old = fetch_node(envlist, "OLDPWD");

	if (commands[1] != NULL)
	{
		tilda = _strcmp(commands[1], "~");
		hyphen = _strcmp(commands[1], "-");
	}

	if (tilda == 0 || commands[1] == NULL)
	{
		path = _strcpy(path, fetched_home->val);
	}
	else if (hyphen == 0)
	{
		path = _strcpy(path, fetched_old->val);
	}
	else if (commands[1][0] == '/')
	{
		path = _strcpy(path, commands[1]);
	}
	else
	{
		getcwd(path, 1024);
		_strncat(path, "/", 1);
		_strncat(path, commands[1], _strlen(commands[1]));
	}


	return (path);
}


/**
 * _cd - builtin cd function
 * @arginv: arg inventory
 *
 * Return: 0 if good, -1 if bad
 */
int _cd(arg_inventory_t *arginv)
{
	char *path;
	char *oldpwd;
	char *pwd;
	char **commands;
	int check;

	oldpwd = safe_malloc(1024);
	pwd = safe_malloc(1024);

	getcwd(oldpwd, 1024);

	commands = (char **)arginv->commands;

	path = yellow_brick_road(commands, arginv->envlist);

	check = chdir(path);

	if (check < 0)
	{
		free(oldpwd);
		free(pwd);
		return (-1);
	}
	else
	{
		getcwd(pwd, 1024);
		modify_node_env(&arginv->envlist, "PWD", pwd);
		modify_node_env(&arginv->envlist, "OLDPWD", oldpwd);
	}

	return (0);
}
