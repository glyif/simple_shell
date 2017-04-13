#include "header.h"

/**
 * exec_builtins - custom function to execute builtin commands
 * @arginv: arguments inventory
 *
 * Return: 1 on success, 0 on failure
 */
int exec_builtins(arg_inventory_t *arginv, int pipein, int pipeout)
{
	int i = 0, j;
	char *str;
	char **commands = (char**)arginv->commands;
	builtins_t builtins_list[] = {

		{"exit", the_exit}, {"monalisa", _monalisa}, {"env", _env},
		{"setenv", _setenv}, {"unsetenv", _unsetenv}, {"history", _history},
		{"cd", _cd},
		{NULL, NULL}
	};
	int old_stdout = 1;
	(void)pipein;

	if (pipeout)
	{
		old_stdout = dup(STDOUT_FILENO); /* Save current stdout */

		if (dup2(pipeout,STDOUT_FILENO) == -1) /* redirect stdout */
		{
			perror("dup2");
			exit(1);
		}
	}

	for (i = 0; (str = builtins_list[i].command) != NULL; i++)
	{
		for (j = 0; commands[j] != NULL; j++)
		{
			if (sp_strncmp(str, commands[j], _strlen(str)) == 0)
			{
				builtins_list[i].builtin_func(arginv);
				return (EXT_SUCCESS);
			}
		}
	}

	if (pipeout)
	{
		if (dup2(old_stdout,STDOUT_FILENO) == -1) /* redirect stdout */
		{
			perror("dup2");
			exit(1);
		}

		close(old_stdout);
	}

	return (EXT_FAILURE);
}

/**
 * exec_path - custom function to execute from PATH
 * @command: arguments inventory
 * @commands: input commands
 * @envlist: linked list to environ variables
 */
pid_t exec_path(char *command, char **commands, env_t *envlist, int pipein, int pipeout)
{
	pid_t pid;
	char **_environ;

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Critical error: unable to fork()!\n");
		exit(1);
	}
	if (pid == 0)
	{
		if (pipein)
		{
			if (dup2(pipein,STDIN_FILENO) == -1) /* redirect STDIN */
			{
				perror("dup2");
				exit(1);
			}
		}

		if(pipeout)
		{
			if(dup2(pipeout,STDOUT_FILENO) == -1) /* redirect stdout */
			{
				perror("dup2");
				exit(1);
			}
		}
		_environ = zelda_to_ganondorf(envlist);

		if (execve(command, commands, _environ) < 0)
		{
			perror("No Command from execve");
			exit(1);
		}
	}
	return pid;
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
pid_t execute(arg_inventory_t *arginv, int pipein, int pipeout)
{
	tokens_t path_token;
	env_t *envlist = arginv->envlist;
	char **commands = (char**) arginv->commands;
	char *path, *command;
	parser_t parser;
	unsigned i;

	command = safe_malloc(BUFSIZE);
	command = _strcpy(command, *commands);
	path = safe_malloc(sizeof(char) * BUFSIZE);

	if (exec_builtins(arginv,pipein,pipeout) == EXT_FAILURE)
	{
		if(is_path(command))
		{
			return exec_path(command, commands, envlist, pipein,pipeout);
		}
		else
		{
			locate_path(path, envlist);
			for(i=0; i<_strlen(path); i++)
				path[i]=(path[i]==':')? ' ' : path[i];
			tokenize(&path_token, path);
			if (!parse(&parser, &path_token))
			{
				cat_path((char**)parser.tree->strings, command);
				return (exec_path(command, commands, envlist, pipein, pipeout));
			}
		}
	}
	return (-1);
}
