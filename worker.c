#include "header.h"

/**
 * worker_execute_core - this is the core execution function
 * @arginv: arg inventory
 *
 * Return: 0
 */
int worker_execute_core(arg_inventory_t *arginv)
{
	int status;
	unsigned int i;	
	int p[2]; /* Set of pipes' descriptors */
	const ptree_t *ptree;
	int fd_input = 0; /* Input file descriptor; soon to be changed with something if there is < command somewhere */
	
	
	for (i = 0; i < arginv->pipeline.processesN; i++)
	{
		if(!_strncmp((char*)arginv->pipeline.processes[i].ptree->strings[0],"exit",4))
		{
			arginv->exit=1;
			break;
		}
		pipe(p); /* Create the two-way pipe */

		/* Actual execution */
		ptree = arginv->pipeline.processes[i].ptree;
		arginv->commands=ptree->strings;

		arginv->pipeline.processes[i].pid = execute(arginv,fd_input,(i + 1 < arginv->pipeline.processesN)? p[1] : 0);
	
		close(p[1]); /* Close non-needed descriptor */
		fd_input = p[0]; /* The input should be saved for the next comman */
	}

	if (!arginv->pipeline.background)
		waitpid(arginv->pipeline.processes[arginv->pipeline.processesN-1].pid,&status,0);
	else
		printf("[x] %i\n", arginv->pipeline.processes[arginv->pipeline.processesN-1].pid);
	
	return (0);
}

/**
 * worker_execute - executes background process
 * @arginv: arginv
 *
 * Return: 0 or exit
 */
int worker_execute(arg_inventory_t *arginv)
{
	return (worker_execute_core(arginv));
}
