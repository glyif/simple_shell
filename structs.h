#ifndef BASE_STRUCTS
#define BASE_STRUCTS
#include "t_struct.h"
#include "p_struct.h"
#include "pa_struct.h"
#include "w_struct.h"

/**
 * struct env - struct for holding custom environmental variables list
 * @var: environmental variable and value separated by '=' char
 * @next: pointer to the next env variable node
 */
typedef struct env
{
	char *var;
	struct env *next;
} env_t;

/**
 * struct arg_inventory - inventory of support arguments for immediate access
 * @input_commands: string of input commands
 * @envlist: custom davinci environ linked list
 * @buflimit: buflimit max of 1024 chars
 */
typedef struct arg_inventory
{
	char *input_commands;
	env_t *envlist;
	const char **commands;
	size_t buflimit;
	int st_mode;
} arg_inventory_t;

/**
 * struct our_builtins - matches command to appropriate builtin function
 * @command: string command for builtin
 * @builtin_func: function to handle builtin command
 */
typedef struct our_builtins
{
	char *command;
	int (*builtin_func)(arg_inventory_t *arginv);
} builtins_t;

#endif
