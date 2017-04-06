#include "header.h"
/**
 * _getline - custom getline currently reads 1 char at a time
 * needs to be updated to read entire stream
 * @buffer: input buffer
 * @limit: maxsize of input character string
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
	return i;
}
/**
 * execute - completes execution
 * @argv: variadic arguments from input
 * Return: void
 */
void execute(char **argv)
{
     pid_t pid;
     int status;

	 pid = fork();

     if (pid < 0)
	 {
		 perror("Process Creation\n");
		 exit(1);
     }
     else if (pid == 0)
	 {
		 if (execvp(*argv, argv) < 0)
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
	char  line[1024];

	while (1)
	{
		write(1, "$ ", 2);
		_getline(line, 1024);
		printf("\n");
		tokenize(&tokens, line);
		execute(tokens.tokens);
	}
	return (0);
}
