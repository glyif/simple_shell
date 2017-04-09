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
			i = read(STDIN_FILENO, (*buffer + charcount), *limit);
			charcount += i;
		}
	}

	return ((ssize_t)(i * (*limit * iterations)));
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
 * main - custom shell
 * Return: 0
 */
int main(void)
{
	arg_inventory_t *arginv;

	arginv = buildarginv();

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		_getline(&arginv->input_commands, &arginv->buflimit);
		tokenize(arginv->tokens, arginv->input_commands);
		execute(arginv);
		mem_reset(arginv->input_commands, BUFSIZE);
		delete_tokens(arginv->tokens);
	}
	return (0);
}
