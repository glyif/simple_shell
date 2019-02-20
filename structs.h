#ifndef STRUCT
#define STRUCT

/**
 * struct token - categorizes a token
 * @id: id of token from TOKEN_ macros
 * @str: token
 * @prec: the prec
 */
typedef struct token
{
	int id;
	char *str;
	int prec;
} token_t;

/**
 * struct tokens - struct for tokenizing string
 * @tokens: array of token_t structs with tokenized strings and ids
 * @tokensN: amount of tokens parsed
 *
 * NOTE: do not deallocate everthing from here until the full parse tree
 * deallocation, because AST will use tokens from this structure!
 */
typedef struct tokens
{
	token_t *tokens;
	unsigned int tokensN;
} tokens_t;

/**
 * struct token_id - baby token
 * @token_id: numerical id
 * @token_str: the exact token string to be compared with
 * @token_descr: for debugging
 * @precedence: the precedence
 */
typedef struct token_id
{
	int token_id;
	const char *token_str;
	const char *token_descr;
	int precedence;
} token_types;

/**
 * struct ptree - base parse tree struct
 * @left: left child node
 * @right: right child node
 * @parent: parent node
 * @token_id: id from macros
 * @strings: corresponding strings, NULL if not TOKEN_STRING
 * @stringsN: amount of strings in strings +1 (for NULL), 0 if not TOKEN_STRING
 */
typedef struct ptree
{
	struct ptree *left;
	struct ptree *right;
	struct ptree *parent;

	int token_id;
	char **strings;
	unsigned int stringsN;
} ptree_t;

/**
 * struct parser - struct to parse
 * @tree: resulting parse tree
 */
typedef struct parser
{
	ptree_t *tree;
} parser_t;

/**
 * struct process - this attributes a parse tree with TOKEN_STRING id with a
 * process id
 * @ptree: ptree to process
 * @pid: pid
 * @io_redir: io_redir
 * @filename: filename
 */
typedef struct process
{
	ptree_t *ptree;
	pid_t pid;
/* 0 for no redirection, 3 for >, 4 >>, 5 < */
	int io_redir;
	char *filename;
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

/**
 * struct env - struct for holding custom environmental variables list
 * @var: environmental variable and value separated by '=' char
 * @val: value of env var
 * @next: pointer to the next env variable node
 */
typedef struct env
{
	char *var;
	char *val;
	struct env *next;
} env_t;

/**
 * struct history - builds linked list of history of input commands
 * @number: command number
 * @command: the input command
 * @next: pointer to next command
 */
typedef struct history
{
	unsigned int number;
	char *command;
	struct history *next;
} history_t;

/**
 * struct alias - matches command with appropriate help text output
 * @alias: the alias
 * @command: the actual command
 * @next: address of next node of alias if present
 */
typedef struct alias
{
	char *alias;
	char *command;
	struct alias *next;
} alias_t;

/**
 * struct arg_inventory - inventory of support arguments for immediate access
 * @input_commands: string of input commands
 * @envlist: custom davinci environ linked list
 * @buflimit: buflimit max of 1024 chars
 * @commands: double pointer to commands list
 * @st_mode: st_mode either FIFO or terminal
 * @history: linked list of history
 * @history_file: the history file to store command history
 * @alias_file: the aliases file to store aliases
 * @alias: linked list of aliases
 * @tokens: tokens list
 * @parser: a parse
 * @pipeline: pipline list
 * @n_bg_jobs: pipeline
 * @pipein: pipein variable
 * @pipeout: pipeout variable
 * @io_redir: io redirection
 * @filename: the filename
 * @last_bg_pid: last pid
 * @exit: indicator to exit or not
 * @exit_status: the exit status
 */
typedef struct arg_inventory
{
	char *input_commands;
	env_t *envlist;
	char **commands;
	size_t buflimit;
	int st_mode;
	history_t *history;
	char *history_file;
	alias_t *alias;
	char *alias_file;
	tokens_t tokens;
	parser_t parser;
	pipeline_t pipeline;
	int n_bg_jobs;
	int pipein;
	int pipeout;
	/* 0 for no redirection, 3 for >, 4 >>, 5 < */
	int io_redir;
	char *filename;

	pid_t last_bg_pid;

	int exit;
	int exit_status;
} arg_inventory_t;

/**
 * struct _builtins - matches command to appropriate builtin function
 * @command: string command for builtin
 * @builtin_func: function to handle builtin command
 */
typedef struct _builtins
{
	char *command;
	int (*builtin_func)(arg_inventory_t *arginv);
} builtins_t;

/**
 * struct bins - matches command to appropriate builtin function
 * @function: string of function name
 * @help: string of name of file
 */
typedef struct bins
{
	char *function;
	void (*help)(void);
} bins_t;

#endif
