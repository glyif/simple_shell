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
 * exec_builtins - custom function to execute builtin commands
 * @commands: input commands from user organized by tokenizer function
 *
 * Return: 1 on success, 0 on failure
 */
int exec_builtins(char **commands)
{
	int i = 0, j;
	char *str;
	builtins_t builtins_list[] = {

		{"exit", builtin_exit}, {"monalisa", builtin_monalisa},
		{NULL, NULL}
	};

	for (i = 0; (str = builtins_list[i].command) != NULL; i++)
		for (j = 0; commands[j] != NULL; j++)
			if (strcmp(str, commands[j]) == 0)
			{
				builtins_list[i].builtin_func(commands);

				return (EXT_SUCCESS);
			}

	return (EXT_FAILURE);
}

/**
 * execute - completes execution of input commands
 * @commands: input commands from user organized by tokenizer function
 * @envlist: custom davinci environmental variables "linked" list
 *
 * Return: void
 */
void execute(char **commands, env_t *envlist)
{
	pid_t pid;
	tokens_t path_token;
	int status;
	char **davinci_environ;
	char *path;
	char *command;

	command = safe_malloc(BUFSIZE);
	command = _strcpy(command, *commands);
	davinci_environ = zelda_to_ganondorf(envlist);
	path = safe_malloc(BUFSIZE);
	locate_path(path, envlist);
	tokenize(&path_token, path);
	cat_path(path_token.tokens, command);
	if (exec_builtins(commands))
	{
		pid = fork();
		if (pid < 0)
			perror("Process Creation\n"), exit(1);
		else if (pid == 0)
			if (execve(command, commands, davinci_environ) < 0)
				perror("No Command"), exit(1);
			else
				_exit(0);
		mem_reset(path, BUFSIZE);
		else
			wait(&status);
	}
}

/**
 * main - custom shell
 * Return: 0
 */
int main(void)
{
	tokens_t tokens;
	arg_inventory_t *arginv;

	arginv = safe_malloc(sizeof(arg_inventory_t));

	arginv->input_commands = safe_malloc(BUFSIZE * sizeof(char));
	arginv->envlist = env_list();
	arginv->buflimit = BUFSIZE;

	if (arginv->envlist == NULL)
	{
		perror("No Memory");
		write(STDOUT_FILENO, "insufficient memory", 19);
	}

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		_getline(&arginv->input_commands, &arginv->buflimit);
		tokenize(&tokens, arginv->input_commands);
		execute(tokens.tokens, arginv->envlist);
		delete_tokens(&tokens);
	}
	return (0);
}
