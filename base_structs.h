#ifndef BASE_STRUCTS
#define BASE_STRUCTS

/**
 * struct tokens - struct for tokenizing string
 * @data: initial string separated with '\0', hold all the tokens
 * @tokens: array of pointers pointing to different parts of the data string
 * @tokensN: amount of tokens parsed
 *
 * NOTE: do not deallocate everthing from here until the full parse tree
 * deallocation, because AST will use tokens from this structure!
 */
typedef struct tokens
{
	char *data;
	char **tokens;
	unsigned int tokensN;
} tokens_t;

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
	tokens_t *tokens;
	size_t buflimit;
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
