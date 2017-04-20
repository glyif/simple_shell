#include "header.h"

/**
 * init_pipeline_count_processes - count amount of token_string in a ptree
 * @tree: pointer to ptree
 *
 * Return: number of processes
 */
unsigned int init_pipeline_count_processes(ptree_t *tree)
{
	if (!tree)
		return (0);

	if (is_redirection(tree->token_id))
		return (1);

	if (tree->token_id == TOKEN_STRING)
		return (1);

	return (init_pipeline_count_processes(tree->left) +
			init_pipeline_count_processes(tree->right));
}

/**
 * init_pipeline_push_processes - fetches everything & puts to pipeline struct
 * @pipeline: pointer to pipeline
 * @tree: ptree to fetch from
 *
 * Return: 0
 */
int init_pipeline_push_processes(pipeline_t *pipeline, ptree_t *tree)
{
	char *filename;

	if (!tree)
		return (0);
	if (is_redirection(tree->token_id))
	{
		pipeline->processes[pipeline->processesN].ptree = tree;
		pipeline->processes[pipeline->processesN].io_redir = tree->token_id;
		filename = safe_malloc(strlen(tree->right->strings[0]) + 1);
		_strcpy(filename, (char *)tree->right->strings[0]);
		pipeline->processes[pipeline->processesN].filename = filename;
		pipeline->processesN++;
		tree->token_id = TOKEN_STRING;
		tree->strings = tree->left->strings;
		tree->stringsN = tree->left->stringsN;
		tree->left->strings = NULL;
		tree->left->stringsN = 0;
		delete_ptree(tree->left);
		delete_ptree(tree->right);
		tree->left = NULL, tree->right = NULL;
		return (0);
	}
	if (tree->token_id == TOKEN_STRING)
	{
		pipeline->processes[pipeline->processesN].ptree = tree;
		pipeline->processes[pipeline->processesN].io_redir = 0;
		pipeline->processes[pipeline->processesN].filename = NULL;
		pipeline->processesN++;
		init_pipeline_push_processes(pipeline, tree->left);
		init_pipeline_push_processes(pipeline, tree->right);
		return (0);
	}
	if (tree->token_id == TOKEN_PIPE)
	{
		init_pipeline_push_processes(pipeline, tree->left);
		init_pipeline_push_processes(pipeline, tree->right);
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
		_perror("No elements present in the pipeline!\n");
		exit(1);
	}

	/* allocate memory */
	pipeline->processes = safe_malloc(mem_needed * sizeof(process_t));
	if (!pipeline->processes)
	{
		_perror("Memory allocation failed!\n");
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
		_perror("uhhhhh number of commands does not match\n");
		exit(1);
	}
	for (i = 0; i < pipeline->processesN; i++)
		pipeline->processes[i].pid = 0;

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
	unsigned int i;

	for (i = 0; i < pipeline->processesN; i++)
		if (pipeline->processes[i].filename != NULL)
			free(pipeline->processes[i].filename);

	free(pipeline->processes);
	pipeline->processes = NULL;
	return (0);
}
