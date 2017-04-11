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
	arginv->buflimit = BUFSIZE;
	arginv->st_mode = _filemode(STDIN_FILENO);

	if (arginv->envlist == NULL)
	{
		perror("No Memory");
		write(STDOUT_FILENO, "insufficient memory", 19);
	}
	
	arginv->exit=0;

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

	while (!arginv->exit)
	{
		if (st_mode)
			write(STDOUT_FILENO, "$ ", 2);
		_getline(&arginv->input_commands, &arginv->buflimit);

		tokenize(&arginv->tokens, arginv->input_commands);

		if(arginv->tokens.tokensN>0)
		{	
			if (parse(&arginv->parser, &arginv->tokens))
			{
				delete_parser(&arginv->parser);
				delete_tokens(&arginv->tokens);
				continue;
			}

			init_pipeline(&arginv->pipeline, arginv->parser.tree);
			worker_execute(arginv);
			delete_pipeline(&arginv->pipeline);
			delete_parser(&arginv->parser);
		}		

		mem_reset(arginv->input_commands, BUFSIZE);

		delete_tokens(&arginv->tokens);
	}
	return (0);
}
