#include "header.h"
/**
 * _getline - custom getline currently reads 1 char at a time
 * @buffer: input buffer
 * @limit: maxsize of input character string
 *
 * Goal: update to make one syscall instead of one sys call per char
 * Return: number of characters written
 */
int _getline(char *buffer, unsigned int limit)
{
	unsigned int i, charcount = 0, iterations = 0;

	i = read(STDIN_FILENO, buffer, limit);
	charcount += i;

	if (i == limit - 1)
	{
		iterations++;
		while (i == limit - 1)
		{
			iterations++;
			buffer = _realloc(buffer, i, limit * iterations);
			i = read(STDIN_FILENO, (buffer + charcount), limit);
			charcount += i;
		}
	}

	return (i * (limit * iterations));
}

/**
 * execdavinci_builtins - custom function to execute builtin commands
 * @commands: input commands from user organized by tokenizer function
 *
 * Return: 1 on success, 0 on failure
 */
int execdavinci_builtins(char **commands)
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
 * @davinci_envlist: custom davinci environmental variables "linked" list
 *
 * Return: void
 */
void execute(char **commands, env_t *davinci_envlist)
{
	pid_t pid;
	int status;
	char **davinci_environ;

	davinci_environ = zelda_to_ganondorf(davinci_envlist);

	if (execdavinci_builtins(commands))
	{
		pid = fork();

		if (pid < 0)
			perror("Process Creation\n"), exit(1);
		else if (pid == 0)
			if (execve(*commands, commands, davinci_environ) < 0)
				perror("No Command"), exit(1);
			else
				_exit(0);
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
	env_t *envp;
	char *line;
	size_t limit = 1024;

	line = safe_malloc(1025 * sizeof(char));
	envp = env_list();
	if (envp == NULL)
	{
		perror("No Memory");
		write(STDOUT_FILENO, "insufficient memory", 19);
	}
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		getline(&line, &limit, stdin);
		tokenize(&tokens, line);
		execute(tokens.tokens, envp);
		delete_tokens(&tokens);
	}
	return (0);
}
