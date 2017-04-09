#include "header.h"

/**
 * exec_builtins - custom function to execute builtin commands
 * @arginv: arguments inventory
 *
 * Return: 1 on success, 0 on failure
 */
int exec_builtins(arg_inventory_t *arginv)
{
	int i = 0, j;
	char *str;
	char **commands = arginv->tokens->tokens;
	builtins_t builtins_list[] = {

		{"exit", the_exit}, {"monalisa", _monalisa}, {"env", _env},
		{"setenv", _setenv},
		{NULL, NULL}
	};

	for (i = 0; (str = builtins_list[i].command) != NULL; i++)
	{
		for (j = 0; commands[j] != NULL; j++)
		{
			if (_strncmp(str, commands[j], _strlen(str)) == 0)
			{
				builtins_list[i].builtin_func(arginv);

				return (EXT_SUCCESS);
			}
		}
	}

	return (EXT_FAILURE);
}

/**
 * exec_path - custom function to execute from PATH
 * @command: arguments inventory
 * @commands: input commands
 * @envlist: linked list to environ variables
 */
void exec_path(char *command, char **commands, env_t *envlist)
{
	pid_t pid;
	int status;
	char **_environ;

	pid = fork();

	if (pid == 0)
	{
		_environ = zelda_to_ganondorf(envlist);

		if (execve(command, commands, _environ) < 0)
		{
			perror("No Command");
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * is_path - checks if input command is part of directory PATH
 * @command: a command
 *
 * Return: 1 if path, 0 if no path
 */
int is_path(char *command)
{
	int i;

	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '/')
			return (1);
		i++;
	}

		return (0);
}

/**
 * execute - completes execution of input commands
 * @arginv: arguments inventory
 *
 * Return: void
 */
void execute(arg_inventory_t *arginv)
{
    tokens_t path_token;
    env_t *envlist = arginv->envlist;
    char **commands = arginv->tokens->tokens;
    char *path, *command;

    command = safe_malloc(BUFSIZE);
    command = _strcpy(command, *commands);
    path = safe_malloc(BUFSIZE);

    if (exec_builtins(arginv) == EXT_FAILURE)
    {
		if(is_path(command))
		{
			exec_path(command, commands, envlist);
		}
		else
		{
			locate_path(path, envlist);
			tokenize(&path_token, path);
			cat_path(path_token.tokens, command);
			exec_path(command, commands, envlist);
		}
	}
}
