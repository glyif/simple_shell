#include "header.h"

/**
 * safe_dup2 - make a dup2 and exit if an error is found
 * @new_fd: file descriptor to use
 * @old_fd: file descriptor to replace
 *
 */
void safe_dup2(int new_fd, int old_fd)
{
	if (dup2(new_fd, old_fd) < 0)
	{
		perror("dup2");
		exit(1);
	}
}

/**
 * redirect_output - redirect stdout depending on the pipeline and the redirection token
 * @arginv: arguments inventory
 * @close_dup: if 1 closes duplicated fd
 *
 * Return: old stdout file descriptor
 */
int redirect_output(arg_inventory_t *arginv, int close_dup)
{
	int stdout_fd;
	int old_stdout;

	/** either a  > or a >> */
	if (arginv->io_redir == TOKEN_REWRITE || arginv->io_redir == TOKEN_APPEND)
	{
		/* it's a > */
		if (arginv->io_redir == TOKEN_REWRITE)
			/* create file for write, create and truncate */
			stdout_fd = open(arginv->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		/* it's a >> */
		else
			/** create file for create and append, does not truncate */
			stdout_fd = open(arginv->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);

	    /* save current stdout */
	    old_stdout = dup(STDOUT_FILENO);

	    /* redirect stdout */
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
		/* save current stdout */
		old_stdout = dup(STDOUT_FILENO);

		/* redirect stdout */
		safe_dup2(arginv->pipeout, STDOUT_FILENO);
	}

	return (old_stdout);
}

/**
 * redirect_input - redirect stdin depending on the pipeline and the redirection token
 * @arginv: arguments inventory
 *
 */
void redirect_input(arg_inventory_t *arginv)
{
	int stdin_fd;

	/* it's a < */
	if (arginv->io_redir == TOKEN_CAT)
	{
		/* open file to read */
		stdin_fd = open(arginv->filename, O_RDONLY);
		safe_dup2(stdin_fd, STDIN_FILENO);

		close(stdin_fd);

		if (arginv->pipein)
			/* unused file descriptor */
			close(arginv->pipein);
	}
	else if (arginv->pipein)
	{
		safe_dup2(arginv->pipein, STDIN_FILENO);
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
