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
	unsigned int i, charcount = 0, iterations = 0;

	i = read(STDIN_FILENO, *buffer, *limit);
	charcount += i;

	if (i <= 0)
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
			i = read(STDIN_FILENO, (*buffer + charcount), *limit);
			charcount += i;
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
	tokens_t tokens;
	parser_t parser;
	pipeline_t pipeline;

	(void)argc, (void)argv, (void)envp;

	arginv = buildarginv();
	st_mode = _filemode(STDIN_FILENO);

	while (TRUE)
	{
		if (st_mode)
			write(STDOUT_FILENO, "$ ", 2);
		_getline(&arginv->input_commands, &arginv->buflimit);

		tokenize(&tokens, arginv->input_commands);

		if (parse(&parser, &tokens))
		{
			delete_parser(&parser);
			delete_tokens(&tokens);
			continue;
		}

		/* execute!!!! */
		init_pipeline(&pipeline, parser.tree);
		worker_execute(&pipeline,arginv);
		delete_pipeline(&pipeline);
		
		mem_reset(arginv->input_commands, BUFSIZE);

		delete_parser(&parser);
		delete_tokens(&tokens);
	}
	return (0);
}
