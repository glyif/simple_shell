#include "header.h"

/**
 * exec_builtins - custom function to execute builtin commands
 * @arginv: arguments inventory
 *
 * Return: 1 on success, 0 on failure
 */
int exec_builtins(arg_inventory_t *arginv)
{
	int i, j, retval, stdout_fd, old_stdout;
	char *str;
	char **commands = (char**)arginv->commands;
	builtins_t builtins_list[] = {

		{"monalisa", _monalisa}, {"env", _env}, {"setenv", _setenv},
		{"unsetenv", _unsetenv}, {"history", _history}, {"cd", _cd},
		{"alias", _alias}, {"unalias", _unalias}, {"help", the_help},
		{NULL, NULL}
	};

	stdout_fd = -1;
	i = 0;

	/** either a  > or a >> */
	if(arginv->io_redir == TOKEN_REWRITE || arginv->io_redir == TOKEN_APPEND)
	{
		/* it's a > */
		if(arginv->io_redir == TOKEN_REWRITE)
			/* create file for write, create and truncate */
            stdout_fd=open(arginv->filename,O_WRONLY | O_CREAT | O_TRUNC,0666);
		/* it's a >> */
		else
			/** create file for create and append, does not truncate */
            stdout_fd=open(arginv->filename,O_WRONLY | O_CREAT | O_APPEND,0666);

		/* save current stdout */
		old_stdout = dup(STDOUT_FILENO);

		/* redirect stdout */
		if (dup2(stdout_fd, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
	}
	else if (arginv->pipeout)
	{
		/* save current stdout */
		old_stdout = dup(STDOUT_FILENO);

		/* redirect stdout */
		if(dup2(arginv->pipeout,STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
	}

	for (i = 0; ((str = builtins_list[i].command) != NULL); i++)
	{
		for (j = 0; commands[j] != NULL; j++)
		{
			if (_strcmp(str, commands[j]) == 0)
			{
				retval = builtins_list[i].builtin_func(arginv);
				break;
			}
		}
	}

	if (arginv->io_redir == TOKEN_REWRITE || arginv->io_redir == TOKEN_APPEND || arginv->pipeout)
	{
		/* revert back to old_stdout */
		if(dup2(old_stdout,STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}

		close(old_stdout);
	}

	return (retval);
}

/**
 * exec_path - custom function to execute from PATH
 * @command: command to execute
 * @arginv: arg inventory
 */
pid_t exec_path(char *command, arg_inventory_t *arginv)
{
	pid_t pid;
	char **_environ;
    int stdin_fd = -1;
    int stdout_fd = -1;

	pid = fork();
	if (pid < 0)
	{
		perror("Critical error: unable to fork()!");
		exit(1);
	}

	if (pid == 0)
	{
		/* it's a < */
		if (arginv->io_redir == TOKEN_CAT)
		{
			/* open file to read */
            stdin_fd = open(arginv->filename,O_RDONLY);

			if(dup2(stdin_fd, STDIN_FILENO) == -1)
			{
				/* redirect STDIN */
				perror("dup2");
				exit(1);
			}  

            close(stdin_fd);
            
			if(arginv->pipein)
				/* unused file descriptor */
                close(arginv->pipein);
		}
		else if (arginv->pipein)
		{
			if (dup2(arginv->pipein, STDIN_FILENO) < 0)
			{
				/* redirect stdin */
				perror("dup2");
				exit(1);
			}  
		}

		/* it's a > or a >> */
		if (arginv->io_redir == TOKEN_REWRITE || arginv->io_redir == TOKEN_APPEND)
		{
			/* it's a > */
    		if (arginv->io_redir == TOKEN_REWRITE)
				/* create file for write, create and truncate */
                stdout_fd=open(arginv->filename,O_WRONLY | O_CREAT | O_TRUNC,0666);
			/* it's a >> */
    		else
				/* create file for write and append, do not truncate */
                stdout_fd=open(arginv->filename,O_WRONLY | O_CREAT | O_APPEND,0666);

			/* redirect stdin */
			if (dup2(stdout_fd, STDOUT_FILENO) < 0)
			{
				perror("dup2");
				exit(1);
			}

            close(stdout_fd);

            if(arginv->pipeout) 
                close(arginv->pipeout);
		}
		else if(arginv->pipeout)
		{
			if(dup2(arginv->pipeout, STDOUT_FILENO) < 0)
			{
				perror("dup2");
				exit(1);
			}  
		}
		_environ = zelda_to_ganondorf(arginv->envlist);

		if (execve(command, (char**)arginv->commands, _environ) < 0)
		{
			perror("No Command");
			exit(1);
		}
	}
	return (pid);
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
pid_t execute(arg_inventory_t *arginv)
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

	if (exec_builtins(arginv) == EXT_FAILURE)
	{
		if(is_path(command))
		{
			return (exec_path(command, arginv));
		}
		else
		{
			locate_path(path, envlist);
			for (i = 0; i < _strlen(path); i++)
				path[i] = (path[i] == ':') ? ' ' : path[i];
			tokenize(&path_token, path);
			if (!parse(&parser, &path_token))
			{
				cat_path((char**)parser.tree->strings, command);
				return (exec_path(command, arginv));
			}
		}
	}
	return (-1);
}
