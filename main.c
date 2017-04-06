#include "header.h"

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

int main(void)
{
	tokens_t tokens;
	char  line[1024];

	while (1)
	{
		printf("$ ");
		fgets(line, sizeof(line), stdin);
		printf("\n");
		tokenize(&tokens, line);
		execute(tokens.tokens);
	}
}
