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
