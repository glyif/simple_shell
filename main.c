#include "header.h"

void  execute(const char **argv)
{
     pid_t pid;
     int status;

	 pid = fork();

     if (pid < 0)
	 {
		 printf("*** ERROR: forking child process failed\n");
		 exit(1);
     }
     else if (pid == 0)
	 {
		 if (execvp(*argv, argv) < 0)
		 {
			 printf("*** ERROR: exec failed\n");
			 exit(1);
		 }
	 }
     else
	 {
		 wait(&status);
     }
}

void  main(void)
{
	tokens_t tokens;
	char  line[1024];

	while (1)
	{
		printf("Shell -> ");
		fgets(line, sizeof(line), stdin);
		printf("\n");
		tokenize(&tokens, line);
		execute(tokens.tokens);
	}
}
