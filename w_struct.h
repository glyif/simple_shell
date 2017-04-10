#ifndef WORKER
#define WORKER
#include "p_struct.h"

/**
 * struct process - this attributes a parse tree with TOKEN_STRING id with a process id
 * @ptree: ptree to process
 * @pid: pid
 */
typedef struct process
{
	const ptree_t *ptree;
	pid_t pid;
} process_t;

/**
 * struct pipeline - struct containing multiple processes
 * @processes: array of processes
 * @processesN: number of processes
 * @background: for background tasks
 * @background_pid: background of pid
 */
typedef struct pipeline
{
	process_t *processes;
	unsigned int processesN;

	unsigned int background;
	pid_t background_pid;
} pipeline_t;
#endif
