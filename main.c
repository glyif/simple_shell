#include "header.h"
/**
 * _getline - custom getline currently reads 1 char at a time
 * @buffer: input buffer
 * @limit: maxsize of input character string
 *
 * Return: number of characters written
 */
ssize_t _getline(char **buffer, size_t *limit)
{
	unsigned int i, j, charcount = 0, iterations = 0, eol = 0;

	j = 0;
	i = -1;
	
	while (j < *limit && i != 0 && !eol)
	{
		i = read(STDIN_FILENO, (*buffer + j), 1);
		eol = ((*buffer + j)[0] == '\n');
		j += i;
	}

	charcount += j;
	if (i == 0)
	{
		free(*buffer);
		exit(EXT_SUCCESS);
	}

	if (i == *limit - 1)
	{
		iterations++;
		while (i == *limit - 1)
		{
			iterations++;
			*buffer = _realloc(*buffer, i, (*limit * iterations));

			j = 0;
			eol = 0;
			while (j < *limit && i != 0 && !eol)
			{
				i = read(STDIN_FILENO, (*buffer + charcount + j), 1);
				eol = ((*buffer + charcount + j)[0] == '\n');
				j += i;
			}

			charcount += j;
		}
	}

	return ((ssize_t)charcount);
}

/**
 * buildarginv - function to build a struct of the arguments inventory
 * Return: pointer to arguments inventory struct
 */
arg_inventory_t *buildarginv(void)
{
	arg_inventory_t *arginv;

	arginv = safe_malloc(sizeof(arg_inventory_t));

	arginv->input_commands = safe_malloc(BUFSIZE * sizeof(char));
	arginv->envlist = env_list();
	arginv->tokens = safe_malloc(sizeof(tokens_t));
	arginv->buflimit = BUFSIZE;

	if (arginv->envlist == NULL)
	{
		perror("No Memory");
		write(STDOUT_FILENO, "insufficient memory", 19);
	}

	return (arginv);
}

/**
 * _filemode - finds file mode of standard input
 * @fd: STDIN_FILENO
 *
 * Return: 1 a device like a terminal, 0 a FIFO special file, or a pipe
 */
int _filemode(int fd)
{
	int result;
	struct stat buf;

	fstat(fd, &buf);

	if (S_ISCHR(buf.st_mode) != 0)
		result = 1;
	else if (S_ISFIFO(buf.st_mode) != 0)
		result = 0;
	else
		result = -1;

	return (result);
}

/**
 * main - custom shell
 * Return: 0
 */
int main(int argc, char **argv, char **envp)
{
	int st_mode;
	arg_inventory_t *arginv;

	(void)argc, (void)argv, (void)envp;

	arginv = buildarginv();
	st_mode = _filemode(STDIN_FILENO);

	while (TRUE)
	{
		if (st_mode)
			write(STDOUT_FILENO, "$ ", 2);
		_getline(&arginv->input_commands, &arginv->buflimit);
		tokenize(arginv->tokens, arginv->input_commands);
		execute(arginv);
		mem_reset(arginv->input_commands, BUFSIZE);
		delete_tokens(arginv->tokens);
	}
	return (0);
}
