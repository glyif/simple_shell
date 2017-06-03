# File List

### support files

  * `man_1_simple_shell`

  	This file contains a man page that can be executed and opened with the
	`man` command either in bash, sh or in **arsine**.

  * `AUTHORS`

  	Contains information on the authors, also listed below in the README

  * `README.md`

  	This file

  * `.travis.yml`

  	supports travis continuous integration for testing github branches before
	merging

### header files (`.h`)

* `header.h`

  All prototypes for all functions, all macros, all included headers from C
  standard library

* `structs.h`

  All struct prototypes

### C language files (`.c`)

* `aliasA.c` and `aliasB.c`

  #### All alias functions

  * `int write_alias(alias_t *head)`

  	prints aliases for testing purpose
  * `alias_t *alias_list(void)`

  	initializes alias list
  * `alias_t *add_node_alias(alias_t **head, char *alias, char *command)`

  	adds new node (struct from linked list) to alias list

* `builtinA.c` and `builtinB.c`

  #### Functions to execute builtins

  * `int _env(arg_inventory_t *arginv)`

  	prints custom environment
  * `int _setenv(arg_inventory_t *arginv)`

  	executes command `setenv` to set new or edit environmental variable
  * `int _unsetenv(arg_inventory_t *arginv)`

  	removes environmental variable
  * `int _history(arg_inventory_t *arginv)`

  	prints working history
  * `int _cd(arg_inventory_t *arginv)`

  	executes command to change directory
  * `int _alias(arg_inventory_t *arginv)`

  	adds new alias
  * `int _unalias(arg_inventory_t *arginv)`

  	removes alias
  * `int the_help(arg_inventory_t *arginv)`

  	prints help message
  * `int the_exit(arg_inventory_t *arginv)`

  	exits arsine

* `cd.c`

  #### functions to work with command cd, change directory

  * `char *yellow_brick_road(char **commands, env_t *envlist)`
  * `env_t *fetch_node(env_t *head, char *var)`

* `executeA.c` and `executeB.c`

  #### functions to execute input commands


  * `pid_t execute(arg_inventory_t *arginv)`
  * `int exec_builtins(arg_inventory_t *arginv)`
  * `pid_t exec_path(char *command, arg_inventory_t *arginv)`
  * `void safe_dup2(int new_fd, int old_fd)`
  * `int redirect_output(arg_inventory_t *arginv, int close_dup)`
  * `void redirect_input(arg_inventory_t *arginv)`

* `environA.c` and `environB.c`

  #### custom environmental variables list, add variables, and change variables

  * `env_t *env_list(void)`

  	initializes custom enviromental variable list
  * `char **separate_string(char *string)`

  	separates a string at the first '=' sign into 2 strings of a `char **` type
  * `unsigned int link_count(env_t *head)`

  	counts number of nodes in environ
  * `char **zelda_to_ganondorf(env_t *head)`

  	converts linked list into `char **` type
  * `env_t *add_node_env(env_t **head, char *var, char *val)`

  	adds new node (struct of linked list) to custom environmental variable list
  * `int modify_node_env(env_t **head, char *new_var, char *new_val)`

  	modifies a node from custom environmental variable list (environ)
  * `int remove_node_env(env_t **head, char *var)`

  removes a node from env list

* `file_io.c`

  #### execute file input and output

  * `ssize_t read_textfile(char *filename, size_t letters)`

  	reads text file and writes to stdout
  * `int trunc_text_to_file(char *filename, char *text_content)`

  	truncates text to file for history list

* `free.c`

  #### functions to free up all linked list and buffers

  * `int freeall(arg_inventory_t *arginv)`

  	function to execute all free functions
  * `int free_environ(env_t *head)`

  	frees custom environ linked list
  * `int free_history(history_t *head)`

  	frees history linked list
  * `int free_alias(alias_t *head)`

  	frees alias linked list

* `getline.c`

  #### custom getline

  * `ssize_t _getline(char **buffer, size_t *limit)`

  	custom getline reads one char at a time and writes to a buffer one at a time
  * `int _filemode(int fd)`

  	checks the st_mode that the shell is being executed from either from terminal or pipe

* `helpA.c` and `helpB.c`

  #### functions to print help information on each function
  These functions write the help builtins help text to stdout.  Each function is named after the help text that it writes.

  * `void h_exit(void)`
  * `void h_monalisa(void)`
  * `void h_env(void)`
  * `void h_setenv(void)`
  * `void h_unsetenv(void)`
  * `void h_history(void)`
  * `void h_cd(void)`
  * `void h_alias(void)`
  * `void h_help(void)`

* `history.c`

  #### prints running total of history

  * `history_t *history_list(arg_inventory_t *arginv)`

  	initializes history linked list
  * `history_t *add_node_history(history_t **head, char *command)`

  	adds new node (struct of linked list) to the history list
  * `int file_history(arg_inventory_t *arginv)`

  	stores history into a file in the $HOME directory

  * `char *history_to_string(history_t *head)`

  	converts history list to a string
  * `history_t *init_history(history_t *head, char *buffer)`

  	used in the initialization function, this function copies old history into current history linked list

* `main.c`

  #### main function and arguments inventory function

  * `int main(void)`

  	main function that is first initialized in our shell
  * `arg_inventory_t *buildarginv(void)`

  	arguments inventory with main arguments utilized throughout our program.  Used to pass multiple arguments into many functions.

* `memmalloc.c`

  #### allocate memory

  * `char *mem_reset(char *str, int bytes)`

  	sets all bytes of memory to '\0' NULL byte, similar to half of calloc() function
  * `void *safe_malloc(int size)`

  	mallocs memory and calls mem_reset()
  * `void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)`

  	reallocates new memory, used for buffer for large inputs

* `parseA.c` and `parseB.c

  #### functions working with parser:

  * `int parse_error(const char *error, token_t *near)`
  * `ptree_t *parse_expr(unsigned int *ntoken, tokens_t *tokens, ptree_t *lhs, int min_prec)`
  * `int parse(parser_t *parser, tokens_t *tokens)`
  * `int delete_parser(parser_t *parser)`
  * `void expand_bash_vars(arg_inventory_t *arginv)`

* `path.c`

  #### functions contianed in this file:

  * `int locate_path(char *path, env_t *envlist)`
  * `int cat_path(char **search_path, char *cmd)`
  * `int is_path(char *command)`

* `pipeline.c`

  #### functions contianed in this file:

  * `unsigned int init_pipeline_count_processes(ptree_t *tree)`
  * `int init_pipeline_push_processes(pipeline_t *pipeline, ptree_t *tree)`
  * `int init_pipeline(pipeline_t *pipeline, ptree_t *ptree)`
  * `int delete_pipeline(pipeline_t * pipeline)`

* `ptree.c`

  #### functions contianed in this file:

  * `ptree_t *ptree_new_node(ptree_t *parent)`
  * `ptree_t *ptree_new_string_node(ptree_t *parent, tokens_t *tokens, unsigned int *cur_token)`
  * `int delete_ptree(ptree_t *node)`
  * `int dump_ptree(ptree_t *ptree, unsigned int depth, int side)`

* `stdlib_funcs.c`

  #### functions contianed in this file:

  * `char _isspace(char c)`
  * `void _perror(char *string)`

  replicates standard library

* `stringsA.c`, `stringsB.c` and `stringsC.c`

  #### functions contianed in this file:

  These functions are mostly all functions that replicate C standard library sting functions.  They are named accordingly

  * `char *_strncpy(char *dest, char *src, int n)`
  * `char *_strdup(char *str)`
  * `unsigned int _strlen(const char *str)`
  * `char *_strcpy(char *dest, char *src)`
  * `char *_strncat(char *dest, char *src, int n)`
  * `int _strcmp(const char *s1, const char *s2)`
  * `int _strncmp(char *s1, char *s2, unsigned int n)`
  * `char *_strcat(char *dest, char *src)`
  * `char *int_to_str(unsigned int n)`
  * `char *_str_replace(char *string, unsigned int start, unsigned int end, char *rep)`
  * `void replace_str(char **old_str, char *new_str, int i, int j, int flg)`

* `tokenize.c` and `tokenizer.c`

  #### functions contianed in this file:

  * `int delete_tokens(tokens_t *tokens)`
  * `int tokenize(tokens_t *tokens, const char *string)`
  * `int dump_token(tokens_t *tokens)`
  * `const char *dump_get_token_descr(int token_id)`
  * `int is_redirection(int token_id)`
  * `void init_tokens(tokens_t *tokens, int length)`

* `worker.c`

  #### functions contianed in this file:

* `int worker_execute_core(arg_inventory_t *arginv)`
* `int worker_execute(arg_inventory_t *arginv)`

* `write.c`

  #### functions contianed in this file:

  These functions all write to standard output

  * `int write_uint(unsigned int n)`

  	writes an integer to string to stdout
  * `unsigned int write_history(history_t *head)`

  	writes history linked list to stdout
  * `void _puts(char *str)`

  	replicates `puts()` from C standard library
  * `size_t print_list(env_t *head)`

  	writes environment linked list to stdout
  * `int _putchar(char c)`

  	replicates C standard library `putchar()`
