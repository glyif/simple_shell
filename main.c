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
		_exit(0);
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

void exec_path(char *command, char **commands, env_t *envlist)
{
	pid_t pid;
	int status;
	char **davinci_environ;

	pid = fork();

	if (pid == 0)
	{
		davinci_environ = zelda_to_ganondorf(envlist);
		
		if (execve(command, commands, davinci_environ) < 0)
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

int is_path(char *command)
{
	int i;

	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '/')
			return (1);
		i++;
	}

		return (0);
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
    tokens_t path_token;
    char *path;
    char *command;

    command = safe_malloc(BUFSIZE);
    command = _strcpy(command, *commands);
	path = safe_malloc(BUFSIZE);

    if (exec_builtins(commands))
    {
		if(is_path(command))
		{
			exec_path(command, commands, envlist);
		}
		else
		{
			locate_path(path, envlist);
			tokenize(&path_token, path);
			cat_path(path_token.tokens, command);
			exec_path(command, commands, envlist);
		}
		
    }
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
	tokens_t tokens;
	arg_inventory_t *arginv;

	arginv = buildarginv();

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		_getline(&arginv->input_commands, &arginv->buflimit);
		tokenize(&tokens, arginv->input_commands);
		execute(tokens.tokens, arginv->envlist);
		mem_reset(arginv->input_commands, BUFSIZE);
		delete_tokens(&tokens);
	}
	return (0);
}
