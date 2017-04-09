#include "header.h"
/**
 * _getline - custom getline currently reads 1 char at a time
 * @buffer: address of pointer to input commands buffer
 * @limit: maxsize of input character string, realloc if necessary
 *
 * Return: number of characters written
 */
ssize_t _getline(char **buffer, size_t *limit)
{
	unsigned int i, j;
	size_t charcount, iterations;

	charcount = 0;
	iterations = 1;
	j = 0;
	i = -1;

	while (i != 0)
	{
		i = read(STDIN_FILENO, (*buffer + j), 1);

		if ((*buffer + j++)[0] == '\n')
		{
			charcount++;
			break;
		}

		if (charcount++ % *limit == 0)
		{
			iterations++;
			*buffer = _realloc(*buffer, charcount, (*limit * iterations));
		}
	}

	if (i == 0)
	{
		free(*buffer);
		exit(EXT_SUCCESS);
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
	arginv->st_mode = _filemode(STDIN_FILENO);

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
	int result = -1;
	struct stat buf;

	fstat(fd, &buf);

	switch (buf.st_mode & S_IFMT)
	{
	case S_IFCHR:
		result = 1;
		break;
	case S_IFIFO:
		result = 0;
		break;
	default:
		break;
	}

	return (result);
}

/**
 * main - custom shell
 * Return: 0
 */
int main(void)
{
	arg_inventory_t *arginv;

	arginv = buildarginv();

	while (TRUE)
	{
		if (arginv->st_mode)
			write(STDOUT_FILENO, "$ ", 2);
		_getline(&arginv->input_commands, &arginv->buflimit);
		tokenize(arginv->tokens, arginv->input_commands);
		execute(arginv);
		mem_reset(arginv->input_commands, BUFSIZE);
		delete_tokens(arginv->tokens);
	}
	return (0);
}
