#include "header.h"

/**
 * init_pipeline_count_processes - count amount of token_string in a ptree
 * @tree: pointer to ptree
 *
 * Return: 0
 */
unsigned int init_pipeline_count_processes(ptree_t *tree)
{
	if (!tree)
		return (0);

	if (tree->token_id == TOKEN_STRING)
		return (1);

	return (init_pipeline_count_processes(tree->left) + init_pipeline_count_processes(tree->right));
}

/**
 * init_pipeline_push_processes - fetches everything and puts into pipeline struct
 * @pipeline: pointer to pipeline
 * @tree: ptree to fetch from
 *
 * Return: 0
 */
int init_pipeline_push_processes(pipeline_t *pipeline, ptree_t *tree)
{
	if (!tree)
		return (0);


	if (tree->token_id == TOKEN_STRING)
	{
		/* Adds string to pipeline */
		pipeline->processes[pipeline->processesN].ptree = tree;
		pipeline->processesN++;

		/* strings should not have childs, but the tree is built */
		/* in a way that there is..... */
		/* so for now we will need to check need to check it */
		init_pipeline_push_processes(pipeline, tree->left);
		init_pipeline_push_processes(pipeline, tree->right);

		return (0);
	}

	if (tree->token_id == TOKEN_PIPE)
	{
		/* Initialize everything from left to right, order matters */
		init_pipeline_push_processes(pipeline, tree->left);
		init_pipeline_push_processes(pipeline, tree->right);
		return (0);
	}

	if (tree->token_id == TOKEN_BACKGROUND)
	{
		/* there is a background task so adjust */
		pipeline->background = 1;
		return (0);
	}

	return (0);
}


/**
 * init_pipeline - initializes pipeline struct
 * @pipeline: pointer to pipeline struct
 * @ptree: ptree to put into pipeline
 *
 * Return: 0
 */
int init_pipeline(pipeline_t *pipeline, ptree_t *ptree)
{
	unsigned int i, mem_needed;

	/* At first, we need to understand how much memory we'll need */
	mem_needed = init_pipeline_count_processes(ptree);
	if (mem_needed == 0)
	{
		perror("No elements present in the pipeline!\n");
		exit(1);
	}

	/* allocate memory */
	pipeline->processes = safe_malloc(mem_needed * sizeof(process_t));

	if (!pipeline->processes)
	{
		perror("Memory allocation failed!\n");
		exit(1);
	}

	/* initializes background service values */
	pipeline->background = 0;
	pipeline->background_pid = 0;

	/* initalizes actual process */
	pipeline->processesN = 0;

	init_pipeline_push_processes(pipeline, ptree);

	if (pipeline->processesN != mem_needed)
	{
		perror("uhhhhh number of commands does not match");
		exit(1);
	}

	for (i = 0; i < pipeline->processesN; i++)
		pipeline->processes[i].pid = 0;

	return (0);
}

/**
 * worker_exec_builtins - custom function to execute builtin commands
 * @arginv: arguments inventory
 *
 * Return: 1 on success, 0 on failure
 */
int worker_exec_builtins(arg_inventory_t *arginv)
{
	int i = 0, j;
	char *str;
	char **commands = (char **)arginv->commands;
	builtins_t builtins_list[] = {

		{"exit", the_exit}, {"monalisa", _monalisa}, {"env", _env},
		{"setenv", _setenv},
		{NULL, NULL}
	};

	for (i = 0; (str = builtins_list[i].command) != NULL; i++)
	{
		for (j = 0; commands[j] != NULL; j++)
		{
			if (_strncmp(str, commands[j], _strlen(str)) == 0)
			{
				builtins_list[i].builtin_func(arginv);

				return (EXT_SUCCESS);
			}
		}
	}

	return (EXT_FAILURE);
}

/**
 * worker_execute_core - this is the core execution function
 * @pipeline: pipeline of commands
 * @arginv: arg inventory
 *
 * Return: 0
 */
int worker_execute_core(pipeline_t *pipeline, arg_inventory_t *arginv)
{

	/* actual executing of processes */
	unsigned int i;
	int status;
	int pid;
	int p[2];
	int fd_input = 0;
	const ptree_t *ptree;

	for (i = 0; i < pipeline->processesN; i++)
	{
		pipe(p);

		pid = fork();
		if (pid < 0)
		{
			perror("Unable to fork()!\n");
			exit(1);
		}

		if (pid == 0)
		{
			dup2(fd_input, 0);

			/* Work with output */
			/* If this is not the last part of the pipeline, we need to dup also */

			if (i + 1 < pipeline->processesN)
				dup2(p[1], 1);

			close(p[0]);

			/* Actual execution */
			ptree = pipeline->processes[i].ptree;
			arginv->commands = pipeline->processes[i].ptree->strings;
			if (worker_exec_builtins(arginv) == EXT_FAILURE)
			{
				execvp(ptree->strings[0], (void *) ptree->strings);
				perror("Command not found\n");
				exit(1);
			}
			else
			{
				exit(0);
			}
		}
		else
		{
			pipeline->processes[i].pid = pid;

			wait(&status);
			close(p[1]);
			/* input should be saved for next command */
			fd_input = p[0];
		}
	}

	return (0);
}

/**
 * worker_execute - executes background process
 * @pipeline: pipeline of commands
 * @arginv: arginv
 *
 * Return: 0 or exit
 */
int worker_execute(pipeline_t *pipeline, arg_inventory_t *arginv)
{
	int pid;

	if (!pipeline->background)
		return (worker_execute_core(pipeline, arginv));

	pid = fork();

	if (pid < 0)
	{
		perror("Unable to fork()!\n");
		exit(1);
	}

	if (pid > 0)
	{
		printf("[x] %i\n", pid);
		return (0);
	}

	worker_execute_core(pipeline, arginv);

	exit(0);
	return (0);
}

/**
 * delete_pipeline - deletes pipeline
 * @pipeline: pointer to pipeline
 *
 * Return: 0
 */
int delete_pipeline(pipeline_t *pipeline)
{
	free(pipeline->processes);
	pipeline->processes = NULL;
	return (0);
}
