#include "header.h"
/**
 * _getline - custom getline currently reads 1 char at a time
 * @buffer: input buffer
 * @limit: maxsize of input character string
 *
 * Goal: update to make one syscall instead of one sys call per char
 * Return: number of characters written
 */
int _getline(char *buffer, int limit)
{
	int i;

	for (i = 0; i < limit - 1; i++)
	{
		read(0, (buffer + i), 1);
		if (buffer[i] == '\n')
			break;
	}
	buffer[++i] = '\0';

	return (i);
}
/**
 * execute - completes execution
 * @argv: input commands from user
 * @envp: environmental variables
 *
 * Return: void
 */
void execute(char **argv, env_t *envp)
{
	pid_t pid;
	int status;
	char **l_to_a;

	pid = fork();

	if (pid < 0)
	{
		perror("Process Creation\n");
		exit(1);
	}
	else if (pid == 0)
	{
		l_to_a = zelda_to_ganondorf(envp);

		if (execve(*argv, argv, l_to_a) < 0)
		{
			perror("No Command");
			exit(1);
		}
	}
	else
	{
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
	char line[1024];

	envp = env_list();
	while (1)
	{
		write(1, "$ ", 2);
		_getline(line, 1024);
		tokenize(&tokens, line);
		execute(tokens.tokens, envp);
	}
	return (0);
}
