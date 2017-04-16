# <img src="https://s3.amazonaws.com/intranet-projects-files/holbertonschool-low_level_programming/235/shell.png" alt="screen shot of custom printf function" style="width:128px;height:128px;"> daVinci

## Description

This repo has our custom shell project, which attempts to replicate some of the
processes of the 'sh' shell or 'bash' shell.

### C language standard functions and system calls utilized

``access``, ``chdir``, ``close``, ``closedir``, ``execve``, ``exit``, ``fork``,
``free``, ``fstat``, ``getcwd``, ``getline``, ``kill``, ``lstat``, ``malloc``,
``open``, ``opendir``, ``perror``, ``read``, ``readdir``, ``signal``, ``stat``,
``strtok``, ``wait``, ``waitpid``, ``wait3``, ``wait4``, ``write``, ``_exit``

## Brief Synopsis

All files in this repository are designed to compile with GNU compiler
collection v. '``gcc 4.8.4``' in the linux environment from '``Ubuntu 14.04.5
LTS``'.  When compiled, the executable file replicates a 'shell' or command line
interpreter, which is a user interface used for access to an operating system's
services.  This shell has a set of custom built-in commands, and also integrates
with other commands located in the system's PATH.  Output and functionality from
commands is designed to replicate output from the shell ``sh`` (dash) and some
bash commands.  For more on the detailed functionality of our shell, please read
our blog posting here:

## File List

### support files

  * ``man_1_simple_shell``

  	This file contains a man page that can be executed and opened with the
	``man`` command either in bash, sh or in our shell daVinci

  * ``AUTHORS``

  	Contains information on the authors, also listed below in the README

  * ``README.md``

  	This file

  * ``.travis.yml``

  	supports travis continuous integration for testing github branches before
	merging

### header files (``.h``)

* ``header.h``

  All prototypes for all functions, all macros, all included headers from C
  standard library

* ``structs.h``

  All struct prototypes

### C language files (``.c``)

* ``alias.c``

  #### All alias functions

  * ``int write_alias(alias_t *head)``

  	prints aliases for testing purpose
  * ``alias_t *alias_list(void)``

  	initializes alias list
  * ``alias_t *add_node_alias(alias_t **head, char *alias, char *command)``

  	adds new node (struct from linked list) to alias list

* ``builtin_funcs.c``

  #### Functions to execute builtins

  * ``int _monalisa(arg_inventory_t *arginv)``

  	easter egg
  * ``int _env(arg_inventory_t *arginv)``

  	prints custom environment
  * ``int _setenv(arg_inventory_t *arginv)``

  	executes command ``setenv`` to set new or edit environmental variable
  * ``int _history(arg_inventory_t *arginv)``

  	prints working history
  * ``int _cd(arg_inventory_t *arginv)``

  	executes command to change directory
  * ``int _alias(arg_inventory_t *arginv)``

  	adds new alias
  * ``int _unalias(arg_inventory_t *arginv)``

  	removes alias
  * ``int the_help(arg_inventory_t *arginv)``

  	prints help message

* ``cd.c``

  #### functions to work with command cd, change directory

  * ``char *yellow_brick_road(char **commands, env_t *envlist)``
  * ``env_t *fetch_node(env_t *head, char *var)``

* ``execfuncs.c``

  #### functions to execute input commands


  * ``pid_t execute(arg_inventory_t *arginv)``
  * ``int exec_builtins(arg_inventory_t *arginv)``
  * ``pid_t exec_path(char *command, arg_inventory_t *arginv)``

* ``file_io.c``

  #### execute file input and output

  * ``ssize_t read_textfile(char *filename, size_t letters)``
  * ``int trunc_text_to_file(char *filename, char *text_content)``

* ``free.c``

  #### functions to free up all linked list and buffers

  * ``int freeall(arg_inventory_t *arginv)``
  * ``int free_environ(env_t *head)``
  * ``int free_history(history_t *head)``
  * ``int free_alias(alias_t *head)``

* ``getline.c``

  #### custom getline

  * ``ssize_t _getline(char **buffer, size_t *limit)``
  * ``int _filemode(int fd)``

* ``help.c``

  #### functions to print help information on each function

  * ``void h_exit(void)``
  * ``void h_monalisa(void)``
  * ``void h_env(void)``
  * ``void h_setenv(void)``
  * ``void h_unsetenv(void)``
  * ``void h_history(void)``
  * ``void h_cd(void)``
  * ``void h_alias(void)``
  * ``void h_help(void)``

* ``history.c``

  #### prints running total of history

  * ``history_t *history_list(arg_inventory_t *arginv)``
  * ``history_t *add_node_history(history_t **head, char *command)``
  * ``int file_history(arg_inventory_t *arginv)``
  * ``char *history_to_string(history_t *head)``
  * ``history_t *init_history(history_t *head, char *buffer)``

* ``linked_helper.c``

  #### custom environmental variables list, add variables, and change variables

  * ``env_t *env_list(void)``
  * ``char **separate_string(char *string)``
  * ``unsigned int link_count(env_t *head)``
  * ``char **zelda_to_ganondorf(env_t *head)``
  * ``env_t *add_node_env(env_t **head, char *var, char *val)``
  * ``int modify_node_env(env_t **head, char *new_var, char *new_val)``
  * ``int remove_node_env(env_t **head, char *var)``

* ``main.c``

  #### main function and arguments inventory function

  * ``int main(void)``
  * ``arg_inventory_t *buildarginv(void)``

* ``memmalloc.c``

  #### allocate memory and set mem to '\0' NULL bytes

  * ``char *mem_reset(char *str, int bytes)``
  * ``void *safe_malloc(int size)``
  * ``void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)``

* ``parse.c``

  #### functions working with parser:

  * ``int parse_error(const char *error, token_t *near)``
  * ``ptree_t *parse_expr(unsigned int *ntoken, tokens_t *tokens, ptree_t *lhs, int min_prec)``
  * ``int parse(parser_t *parser, tokens_t *tokens)``
  * ``int delete_parser(parser_t *parser)``
  * ``void expand_bash_vars(arg_inventory_t *arginv)``

* ``path.c``

  #### functions contianed in this file:

  * ``int locate_path(char *path, env_t *envlist)``
  * ``int cat_path(char **search_path, char *cmd)``
  * ``int is_path(char *command)``

* ``pipeline.c``

  #### functions contianed in this file:

  * ``unsigned int init_pipeline_count_processes(ptree_t *tree)``
  * ``int init_pipeline_push_processes(pipeline_t *pipeline, ptree_t *tree)``
  * ``int init_pipeline(pipeline_t *pipeline, ptree_t *ptree)``
  * ``int delete_pipeline(pipeline_t * pipeline)``

* ``ptree.c``

  #### functions contianed in this file:

  * ``ptree_t *ptree_new_node(ptree_t *parent)``
  * ``ptree_t *ptree_new_string_node(ptree_t *parent, tokens_t *tokens, unsigned int *cur_token)``
  * ``int delete_ptree(ptree_t *node)``
  * ``int dump_ptree(ptree_t *ptree, unsigned int depth, int side)``

* ``stdlib_funcs.c``

  #### functions contianed in this file:

  * ``char _isspace(char c)``

* ``strings.c``

  #### functions contianed in this file:

  * ``char *_strncpy(char *dest, char *src, int n)``
  * ``char *_strdup(char *str)``
  * ``unsigned int _strlen(const char *str)``
  * ``char *_strcpy(char *dest, char *src)``
  * ``char *_strncat(char *dest, char *src, int n)``
  * ``int _strcmp(const char *s1, const char *s2)``
  * ``int _strncmp(char *s1, char *s2, unsigned int n)``
  * ``int _unsetenv(arg_inventory_t *arginv)``
  * ``char *_strcat(char *dest, char *src)``
  * ``char *int_to_str(unsigned int n)``
  * ``char *_str_replace(char *string, unsigned int start, unsigned int end, char *rep)``

* ``tokenizer.c``

  #### functions contianed in this file:

  * ``int delete_tokens(tokens_t *tokens)``
  * ``int tokenize(tokens_t *tokens, const char *string)``
  * ``int dump_token(tokens_t *tokens)``
  * ``const char *dump_get_token_descr(int token_id)``
  * ``int is_redirection(int token_id)``

* ``worker.c``

  #### functions contianed in this file:

*  ``int worker_execute_core(arg_inventory_t *arginv)``
* ``int worker_execute(arg_inventory_t *arginv)``

* ``write.c``

  #### functions contianed in this file:

  * ``int write_uint(unsigned int n)``
  * ``unsigned int write_history(history_t *head)``
  * ``void _puts(char *str)``
  * ``size_t print_list(env_t *head)``
  * ``int _putchar(char c)``


## Authors

Bobby Yang - https://github.com/bobstermyang/  
David John Coleman II - http://www.davidjohncoleman.com/

## License

Public Domain, no copyright protection
