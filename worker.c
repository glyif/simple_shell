#include "header.h"

/**
 * worker_execute_core - this is the core execution function
 * @arginv: arg inventory
 *
 * Return: 0
 */
pid_t worker_execute_core(arg_inventory_t *arginv)
{
	unsigned int i;
	/*int p[2]; Set of pipes' descriptors */
	const ptree_t *ptree;
	/* int fd_input = 0; */ /* Input file descriptor; soon to be changed with
						 something if there is < command somewhere */

	for (i = 0; i < arginv->pipeline.processesN; i++)
	{
		ptree = arginv->pipeline.processes[i].ptree;
		arginv->commands = ptree->strings;
			expand_alias(arginv);
		/* pipe(p); Create the two-way pipe */

		/*
		arginv->pipein = fd_input;
		arginv->pipeout = (i + 1 < arginv->pipeline.processesN) ? p[1] : 0;
		*/

		if (arginv->pipeline.processes[i].io_redir)
		{
			arginv->filename = arginv->pipeline.processes[i].filename;
			/* arginv->io_redir = arginv->pipeline.processes[i].io_redir; */
		}
		else
		{
			arginv->filename = NULL;
			arginv->io_redir = 0;
		}

		arginv->pipeline.processes[i].pid = execute(arginv);
		/*
		close(p[1]);
		*/
		/*fd_input = p[0];The input should be saved for the next comman */
	}

	return (arginv->pipeline.processes[arginv->pipeline.processesN - 1].pid);
}

pid_t worker_execute_tree(arg_inventory_t *arginv, ptree_t *ptree,
						  unsigned int depth)
{
	int status;
	pid_t last_pid = -1;
	int execute;

	if (!ptree)
		return (last_pid);

	/* execute pipeline */
	if (ptree->token_id == TOKEN_STRING || ptree->token_id == TOKEN_PIPE ||
		is_redirection(ptree->token_id))
	{
	    init_pipeline(&arginv->pipeline, ptree);
	    last_pid = worker_execute_core(arginv);
		delete_pipeline(&arginv->pipeline);
		return (last_pid);
	}

	/* recursive call on each child */
	if (ptree->left)
	{
		last_pid = worker_execute_tree(arginv, ptree->left, depth + 1);

		if (ptree->token_id != TOKEN_BACKGROUND)
		{
			/* wait for the child */
			waitpid(last_pid, &status, 0);

			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else
				status = 1;
		}
		else
		{
			arginv->n_bg_jobs++;
			arginv->last_bg_pid = last_pid;
			status = 0;
		}

		arginv->last_exit_code = status;
		execute = 1;

		if (ptree->token_id == TOKEN_AND)
		{
			if (status != EXIT_SUCCESS)
				execute = 0;
		}
		else if (ptree->token_id == TOKEN_OR)
		{
			if (status == EXIT_SUCCESS)
				execute = 0;
		}
		if (execute)
			last_pid = worker_execute_tree(arginv, ptree->right, depth + 1);
	}
	return (last_pid);
}

/**
 * worker_execute - executes background process
 * @arginv: arginv
 *
 * Return: 0 or exit
 */
int worker_execute(arg_inventory_t *arginv)
{
	pid_t last_pid;
	int status;

	arginv->n_bg_jobs = 0;

	last_pid = worker_execute_tree(arginv, arginv->parser.tree, 0);

	if (last_pid != -1)
	{
		if (arginv->parser.tree->token_id != TOKEN_BACKGROUND)
		{
			waitpid(last_pid, &status, 0);

			status = 1;
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
		}
		else
		{
			arginv->n_bg_jobs++;
			arginv->last_bg_pid = last_pid;
			status = 0;
		}
		arginv->last_exit_code = status;
	}
	return (0);
}
