#include "header.h"

/**
 * safe_dup2 - make a dup2 and exit if an error is found
 * @new_fd: file descriptor to use
 * @old_fd: file descriptor to replace
 *
 */
/*
void safe_dup2(int new_fd, int old_fd)
{
	if (dup2(new_fd, old_fd) < 0)
	{
		_perror("cannot duplicate\n");
		exit(1);
	}
}
*/

/**
 * redirect_output - redirect stdout depending on the pipeline & redirect token
 * @arginv: arguments inventory
 * @close_dup: if 1 closes duplicated fd
 *
 * Return: old stdout file descriptor
 */
/*int redirect_output(arg_inventory_t *arginv, int close_dup)
{
	int stdout_fd;
	int old_stdout;

	if (arginv->io_redir == TOKEN_REWRITE || arginv->io_redir == TOKEN_APPEND)
	{
		if (arginv->io_redir == TOKEN_REWRITE)
			stdout_fd = open(arginv->filename, O_WRONLY | O_CREAT | O_TRUNC,
							 0666);
		else
			stdout_fd = open(arginv->filename, O_WRONLY | O_CREAT | O_APPEND,
							 0666);
	    old_stdout = dup(STDOUT_FILENO);
	    safe_dup2(stdout_fd, STDOUT_FILENO);
		if (close_dup)
		{
			close(stdout_fd);
			if (arginv->pipeout)
				close(arginv->pipeout);
		}
	}
	else if (arginv->pipeout)
	{
		old_stdout = dup(STDOUT_FILENO);

		safe_dup2(arginv->pipeout, STDOUT_FILENO);
	}
	return (old_stdout);
}
*/
/**
 * redirect_input - redirect stdin depending on the pipeline & redirect token
 * @arginv: arguments inventory
 *
 */
/*
int redirect_input(arg_inventory_t *arginv)
{
	int stdin_fd;

	if (arginv->io_redir == TOKEN_CAT)
	{
		stdin_fd = open(arginv->filename, O_RDONLY);
		
		if (stdin_fd < 0)
			return -1;

		safe_dup2(stdin_fd, STDIN_FILENO);

		close(stdin_fd);

		if (arginv->pipein)
			close(arginv->pipein);
	}
	else if (arginv->pipein)
	{
		safe_dup2(arginv->pipein, STDIN_FILENO);
	}

	return (0);
}
*/

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
