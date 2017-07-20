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
	/* int p[2]; Set of pipes' descriptors */
	ptree_t *ptree;
	/**
	 * int fd_input = 0; Input file descriptor; soon to be changed with
	 * something if there is < command somewhere
	 */

	for (i = 0; i < arginv->pipeline.processesN; i++)
	{
		ptree = arginv->pipeline.processes[i].ptree;
		arginv->commands = ptree->strings;
		ptree->stringsN += expand_alias(arginv);
		ptree->strings = arginv->commands;
		/* pipe(p); Create the two-way pipe */
		/**
		 * arginv->pipein = fd_input;
		 * arginv->pipeout = (i + 1 < arginv->pipeline.processesN) ? p[1] : 0;
		 *
		 *		if (arginv->pipeline.processes[i].io_redir)
		 *		{
		 *			arginv->filename = arginv->pipeline.processes[i].filename;
		 *			arginv->io_redir = arginv->pipeline.processes[i].io_redir;
		 *		}
		 *		else
		 *		{
		 *			arginv->filename = NULL;
		 *			arginv->io_redir = 0;
		 *		}
		 */
		arginv->pipeline.processes[i].pid = execute(arginv);
		/**
		 * close(p[1]); Close non-needed descriptor
		 * fd_input = p[0];  The input should be saved for the next comman
		 */
	}
	return (arginv->pipeline.processes[arginv->pipeline.processesN - 1].pid);
}

/**
 * worker_execute_tree - this executes ptree
 * @arginv: arg inventory
 * @ptree: the parsing tree
 * @depth: the depth of parsing tree
 *
 * Return: the last pid
 */
pid_t worker_execute_tree(arg_inventory_t *arginv, ptree_t *ptree,
						  unsigned int depth)
{
	int status = 0, id, execute = 1;
	pid_t last_pid = -1;

	if (!ptree)
		return (last_pid);
	id = ptree->token_id;
	if (id == TOKEN_STRING || id == TOKEN_PIPE || is_redirection(id))
	{ /* execute pipeline */
		init_pipeline(&arginv->pipeline, ptree);
		last_pid = worker_execute_core(arginv);
		delete_pipeline(&arginv->pipeline);
		return (last_pid);
	} /* recursive call on each child */
	if (ptree->left)
	{
		last_pid = worker_execute_tree(arginv, ptree->left, depth + 1);
		if (id != TOKEN_BACKGROUND)
		{ /* wait for the child */
			waitpid(last_pid, &status, 0);
			status = WEXITSTATUS(status);
		}
		else
			arginv->n_bg_jobs++, arginv->last_bg_pid = last_pid;
		switch (status)
		{
		case 1:
			arginv->exit_status = 127;
			break;
		default:
			arginv->exit_status = status;
			break;
		}
		if ((id == TOKEN_AND && status) || (id == TOKEN_OR && !status))
			execute = 0;
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
	int status = 0;

	arginv->n_bg_jobs = 0;

	last_pid = worker_execute_tree(arginv, arginv->parser.tree, 0);

	if (last_pid != -1)
	{
		if (arginv->parser.tree->token_id != TOKEN_BACKGROUND)
		{
			waitpid(last_pid, &status, 0);
			status = WEXITSTATUS(status);
		}
		else
		{
			arginv->n_bg_jobs++;
			arginv->last_bg_pid = last_pid;
		}
		switch (status)
		{
		case 1:
			arginv->exit_status = 127;
			break;
		default:
			arginv->exit_status = status;
			break;
		}
	}
	return (0);
}
