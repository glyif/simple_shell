![Holberton logo](https://www.holbertonschool.com/assets/holberton-logo-1cc451260ca3cd297def53f2250a9794810667c7ca7b5fa5879a569a457bf16f.png)

# Your Document Title

## Author: Bobby Yang (Description)

## Paragraph Header
You can type any text information in this paragraph block. All the
Markdown (md) decorators can be use inside here in order to markup
your text, they will be keep as-is while being parsed.

## File Breakdown

### 1 - aliasA.c


##### Function: *alias_list

```c
alias_t *alias_list(void)
```

alias_list - builtin func to set alias list

###### Returns
- 0 on success

##### Function: *add_node_alias

```c
alias_t *add_node_alias(alias_t **head, char *alias, char *command)
```

add_node_alias - builtin func to set alias

###### Params
- `@head` head of alias list
- `@alias` alias ot add
- `@command` actual command equivalent to alias

###### Returns
- 0 on success

##### Function: modify_node_alias

```c
int modify_node_alias(alias_t **head, char *new_var, char *new_val)
```

modify_node_alias - checks to see if node exists, and modifies it if so.

###### Params
- `@head` beginning of linked list
- `@new_var` variable to modify
- `@new_val` new string to be modified to found node

###### Returns
- pointer to new node or NULL if fail

##### Function: remove_node_alias

```c
int remove_node_alias(alias_t **head, char *var)
```

remove_node_alias - removes node from linked list

###### Params
- `@head` beginning of linked list
- `@var` var of node to be removed from linked list

###### Returns
- pointer to new node or NULL

##### Function: write_alias

```c
int write_alias(alias_t *head)
```

write_alias - function to write alias list to stdout for testing

###### Params
- `@head` head of alias list

###### Returns
- chars written

### 2 - aliasB.c


##### Function: save_alias

```c
int save_alias(arg_inventory_t *arginv)
```

save_alias - saves alias definitions to  file

###### Params
- `@arginv` arguments inventory

###### Returns
- 0 success, 1 failure

##### Function: load_alias

```c
int load_alias(arg_inventory_t *arginv)
```

load_alias - loads alias definitions from file

###### Params
- `@arginv` arguments inventory

###### Returns
- 0 success, 1 failure

##### Function: *fetch_node_alias

```c
alias_t *fetch_node_alias(alias_t *head, char *var)
```

fetch_node_alias - fetches a node of a given alias

###### Params
- `@head` head of list
- `@var` alias to match of the node to fetch

###### Returns
- fetched node or NULL

### 3 - builtinA.c


##### Function: _env

```c
int _env(arg_inventory_t *arginv)
```

_env - writes env to stdout

###### Params
- `@arginv` arguments inventory

###### Returns
- 0 on success

##### Function: _history

```c
int _history(arg_inventory_t *arginv)
```

_history - writes history to stdout

###### Params
- `@arginv` arguments inventory

###### Returns
- 0 on success

##### Function: _setenv

```c
int _setenv(arg_inventory_t *arginv)
```

_setenv - sets new environmental variable

###### Params
- `@arginv` arguments inventory

###### Returns
- 0 on success

##### Function: _unsetenv

```c
int _unsetenv(arg_inventory_t *arginv)
```

_unsetenv - sets new environmental variable

###### Params
- `@arginv` arguments inventory

###### Returns
- 0 on success

##### Function: _arsine

```c
int _arsine(arg_inventory_t *arginv)
```

_arsine - prints mona lisa ascii art

###### Params
- `@arginv` arguments inventory

###### Returns
- 0 on success

### 4 - builtinB.c


##### Function: _alias

```c
int _alias(arg_inventory_t *arginv)
```

_alias - builtin func to set alias

###### Params
- `@arginv` arguments inventory

###### Returns
- 0 on success

##### Function: _unalias

```c
int _unalias(arg_inventory_t *arginv)
```

_unalias - builtin func to unset alias

###### Params
- `@arginv` arguments inventory

###### Returns
- 0 on success

##### Function: the_help

```c
int the_help(arg_inventory_t *arginv)
```

the_help - prints mona lisa ascii art

###### Params
- `@arginv` arguments inventory

###### Returns
- 0 on success

##### Function: the_exit

```c
int the_exit(arg_inventory_t *arginv)
```

the_exit - exit status to exit

###### Params
- `@arginv` arguments inventory

###### Returns
- 0 on success

### 5 - cd.c


##### Function: *yellow_brick_road

```c
char *yellow_brick_road(char **commands, env_t *envlist)
```

yellow_brick_road - assembles path to cd into

###### Params
- `@commands` array of pointer pointg to commands
- `@envlist` head of env linked list

###### Returns
- full filepath

##### Function: _cd

```c
int _cd(arg_inventory_t *arginv)
```

_cd - builtin cd function

###### Params
- `@arginv` arg inventory

###### Returns
- 0 if good, -1 if bad

### 6 - environA.c


##### Function: link_count

```c
unsigned int link_count(env_t *head)
```

link_count - counts number of nodes in linked list

###### Params
- `@head` pointer to head of linked list

###### Returns
- number of nodes

##### Function: *env_list

```c
env_t *env_list(void)
```

env_list - creates a linked list of all environ variables

###### Returns
- head (pointer to first node of linked list of environ variables)

### 7 - environB.c


##### Function: *add_node_env

```c
env_t *add_node_env(env_t **head, char *var, char *val)
```

add_node_env - adds new node to end of linked list

###### Params
- `@head` beginning of linked list
- `@var` variable to be added
- `@val` value to be added

###### Returns
- pointer to new node

##### Function: modify_node_env

```c
int modify_node_env(env_t **head, char *new_var, char *new_val)
```

modify_node_env - checks to see if node exists, and modifies it if so.

###### Params
- `@head` beginning of linked list
- `@new_var` variable to modify
- `@new_val` new string to be modified to found node

###### Returns
- pointer to new node or NULL if fail

##### Function: remove_node_env

```c
int remove_node_env(env_t **head, char *var)
```

remove_node_env - removes node from linked list

###### Params
- `@head` beginning of linked list
- `@var` var of node to be removed from linked list

###### Returns
- pointer to new node or NULL

##### Function: *fetch_node

```c
env_t *fetch_node(env_t *head, char *var)
```

fetch_node - fetches a node of a given var

###### Params
- `@head` head of list
- `@var` value to match of the node to fetch

###### Returns
- fetched node or head

### 8 - executeA.c


##### Function: exec_builtins

```c
int exec_builtins(arg_inventory_t *arginv)
```

exec_builtins - custom function to execute builtin commands

###### Params
- `@arginv` arguments inventory

###### Returns
- 1 on success, 0 on failure

##### Function: exec_error_exit

```c
void exec_error_exit(char *msg, char *command, char **_environ,
		arg_inventory_t *arginv)
```

exec_error_exit - frees all and exits if exec error

###### Params
- `@msg` message to display
- `@command` command to free
- `@_environ` env double pointer to free
- `@arginv` arg inventory to free

##### Function: exec_path

```c
pid_t exec_path(char *command, arg_inventory_t *arginv)
```

exec_path - custom function to execute from PATH

###### Params
- `@command` command to execute
- `@arginv` arg inventory

###### Returns
- pid of parent

##### Function: execute

```c
pid_t execute(arg_inventory_t *arginv)
```

execute - completes execution of input commands

###### Params
- `@arginv` arguments inventory

###### Returns
- void

### 9 - executeB.c


##### Function: is_path

```c
int is_path(char *command)
```

is_path - checks if input command is part of directory PATH

###### Params
- `@command` a command

###### Returns
- 1 if path, 0 if no path

### 10 - file_io.c


##### Function: read_textfile

```c
ssize_t read_textfile(char *filename, size_t letters)
```

read_textfile - reads a text file and prints it to the POSIX stdout

###### Params
- `@filename` the file
- `@letters` number of letters to print

###### Returns
- actual number of letters it could read and print

##### Function: trunc_text_to_file

```c
int trunc_text_to_file(char *filename, char *text_content)
```

trunc_text_to_file - appends text to the end of a file

###### Params
- `@filename` name of file to have text appended to
- `@text_content` text to be appended to the file

###### Returns
- 1 on success, -1 on failure

##### Function: append_text_to_file

```c
int append_text_to_file(char *filename, char *text_content)
```

append_text_to_file - appends text to the end of a file

###### Params
- `@filename` name of file to have text appended to
- `@text_content` text to be appended to the file

###### Returns
- 1 on success, -1 on failure

### 11 - free.c


##### Function: freeall

```c
int freeall(arg_inventory_t *arginv)
```

freeall - function to free all allocated memory

###### Params
- `@arginv` args inventory

###### Returns
- 0 on success, 1 on failure

##### Function: free_alias

```c
int free_alias(alias_t *head)
```

free_alias - function to free all allocated memory

###### Params
- `@head` head of alias

###### Returns
- 0 on success, 1 on failure

##### Function: free_environ

```c
int free_environ(env_t *head)
```

free_environ - function to free all allocated memory

###### Params
- `@head` head of custom _environ

###### Returns
- 0 on success, 1 on failure

##### Function: free_history

```c
int free_history(history_t *head)
```

free_history - function to free all allocated memory

###### Params
- `@head` history linked list

###### Returns
- 0 on success, 1 on failure

### 12 - getline.c


##### Function: _getline

```c
ssize_t _getline(char **buffer, size_t *limit)
```

_getline - custom getline currently reads 1 char at a time

###### Params
- `@buffer` address of pointer to input commands buffer
- `@limit` maxsize of input character string, realloc if necessary

###### Returns
- number of characters written

##### Function: _readline

```c
ssize_t _readline(int fd, char **buffer, size_t *limit)
```

_readline - custom getline currently reads 1 char at a time from a file descriptor

###### Params
- `@fd` file descriptor of the file to use for reading
- `@buffer` address of pointer to input commands buffer
- `@limit` maxsize of input character string, realloc if necessary

###### Returns
- number of characters written

##### Function: _filemode

```c
int _filemode(int fd)
```

_filemode - finds file mode of standard input

###### Params
- `@fd` STDIN_FILENO

###### Returns
- 1 a device like a terminal, 0 a FIFO special file, or a pipe

### 13 - helpA.c


##### Function: h_alias

```c
void h_alias(void)
```

h_alias - help function to explain how the associated function works

##### Function: h_cd

```c
void h_cd(void)
```

h_cd - help function to explain how the associated function works

##### Function: h_env

```c
void h_env(void)
```

h_env - help function to explain how the associated function works

##### Function: h_exit

```c
void h_exit(void)
```

h_exit - help function to explain how the associated function works

##### Function: h_help

```c
void h_help(void)
```

h_help - help function to explain how the associated function works

### 14 - helpB.c


##### Function: h_history

```c
void h_history(void)
```

h_history - help function to explain how the associated function works

##### Function: h_monalisa

```c
void h_monalisa(void)
```

h_monalisa - help function to explain how the associated function works

##### Function: h_setenv

```c
void h_setenv(void)
```

h_setenv - help function to explain how the associated function works

##### Function: h_unsetenv

```c
void h_unsetenv(void)
```

h_unsetenv - help function to explain how the associated function works

### 15 - history.c


##### Function: *history_list

```c
history_t *history_list(arg_inventory_t *arginv)
```

history_list - initializes linked list of history from history file in $HOME

###### Params
- `@arginv` arguments inventory

###### Returns
- head (pointer to first node of linked list of environ variables)

##### Function: *init_history

```c
history_t *init_history(history_t *head, char *buffer)
```

init_history - initializes history using history file converted to buffer

###### Params
- `@head` head of linked list of history commands
- `@buffer` old history backup converted to string

###### Returns
- head (pointer to first node of linked list of environ variables)

##### Function: *add_node_history

```c
history_t *add_node_history(history_t **head, char *command)
```

add_node_history - adds new node to end of linked list of input history

###### Params
- `@head` head of history linked list
- `@command` new command

###### Returns
- pointer to new node

##### Function: file_history

```c
int file_history(arg_inventory_t *arginv)
```

file_history - converts history to string to file in history file

###### Params
- `@arginv` arguments inventory

###### Returns
- 0 success, 1 failure

##### Function: *history_to_string

```c
char *history_to_string(history_t *head)
```

history_to_string - converts history linked list to string

###### Params
- `@head` head of linked list of history

###### Returns
- linked list converted to string

### 16 - main.c


##### Function: *buildarginv

```c
arg_inventory_t *buildarginv(void)
```

buildarginv - function to build a struct of the arguments inventory

###### Returns
- pointer to arguments inventory struct

##### Function: sig_handler

```c
void sig_handler(int sig)
```

sig_handler - handles user input of ^C with the following

###### Params
- `@sig` integer value of signal to change, will be SIGINT = ^C

###### Returns
- void

##### Function: main

```c
int main(void)
```

main - custom shell

###### Returns
- 0

### 17 - memmalloc.c


##### Function: *_realloc

```c
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
```

_realloc - reallocates a memory block using malloc and free

###### Params
- `@ptr` pointer to reallocate memory
- `@old_size` size in bytes of allocated memory
- `@new_size` newsize of memory block in bytes

###### Returns
- void pointer to new allocation of memory

##### Function: *mem_reset

```c
char *mem_reset(char *str, int bytes)
```

mem_reset - sets all bytes of string to '\0'

###### Params
- `@str` string
- `@bytes` number of bytes

###### Returns
- pointer to string with reset mem

##### Function: *safe_malloc

```c
void *safe_malloc(int bytes)
```

safe_malloc - mallocs memory of size bytes, prints error message on error

###### Params
- `@bytes` number of bytes to malloc

###### Returns
- pointer to malloced memory or NULL

### 18 - parseA.c


##### Function: parse_error

```c
int parse_error(token_t *near)
```

parse_error - prints parser error

###### Params
- `@near` where the issue is at

###### Returns
- 1 because of error

##### Function: *parse_expr

```c
ptree_t *parse_expr(unsigned int *ntoken, tokens_t *tokens, ptree_t *lhs,
					int min_prec)
```

parse_expr - operator precedence parser

###### Params
- `@ntoken` token number;
- `@tokens` tokens_t struct;
- `@lhs` left hand side;
- `@min_prec` minimum precedent

###### Returns
- pointer to built tree

##### Function: parse

```c
int parse(parser_t *parser, tokens_t *tokens)
```

parse - main funciton that creates the entire parse tree from the tokenizer

###### Params
- `@parser` parser_t struct
- `@tokens` tokens_t struct

###### Returns
- 0

##### Function: delete_parser

```c
int delete_parser(parser_t *parser)
```

delete_parser - frees parser struct

###### Params
- `@parser` parser struct

###### Returns
- 0;

### 19 - parseB.c


##### Function: _getpid

```c
int _getpid(void)
```

##### Function: bash_replace

```c
void bash_replace(arg_inventory_t *arginv, int index)
```

bash_replace - replaces env vars

###### Params
- `@arginv` arg inventory
- `@index` index of token_t struct array

##### Function: expand_bash_vars

```c
void expand_bash_vars(arg_inventory_t *arginv)
```

expand_bash_vars - expand all variables found in the arginv strings

###### Params
- `@arginv` args inventory

##### Function: expand_alias

```c
int expand_alias(arg_inventory_t *arginv)
```

expand_alias - expand the alias found in the command strings

###### Params
- `@arginv` args inventory

###### Returns
- int

### 20 - path.c


##### Function: locate_path

```c
int locate_path(char *path, env_t *envlist)
```

locate_path - finds the val of PATH env

###### Params
- `@path` pointer to path buffer
- `@envlist` pointer to envlist linked list

###### Returns
- 1 if found, 0 if not

##### Function: cat_path

```c
int cat_path(char **search_path, char *cmd)
```

cat_path - cats command to path to search if it's valid command in path

###### Params
- `@search_path` env to search
- `@cmd` command to search for

###### Returns
- 0 if found, -1 if not found

##### Function: count_paths

```c
int count_paths(char *path_str)
```

count_paths - count how many paths are in the PATH string

###### Params
- `@path_str` PATH env ar

###### Returns
- number of paths found

##### Function: free_paths

```c
void free_paths(char **paths)
```

free_paths - frees the array of paths

###### Params
- `@paths` paths

### 21 - pipeline.c


##### Function: init_pipeline_count_processes

```c
unsigned int init_pipeline_count_processes(ptree_t *tree)
```

init_pipeline_count_processes - count amount of token_string in a ptree

###### Params
- `@tree` pointer to ptree

###### Returns
- number of processes

##### Function: init_pipeline_push_processes

```c
int init_pipeline_push_processes(pipeline_t *pipeline, ptree_t *tree)
```

init_pipeline_push_processes - fetches everything & puts to pipeline struct

###### Params
- `@pipeline` pointer to pipeline
- `@tree` ptree to fetch from

###### Returns
- 0

##### Function: init_pipeline

```c
int init_pipeline(pipeline_t *pipeline, ptree_t *ptree)
```

init_pipeline - initializes pipeline struct

###### Params
- `@pipeline` pointer to pipeline struct
- `@ptree` ptree to put into pipeline

###### Returns
- 0

##### Function: delete_pipeline

```c
int delete_pipeline(pipeline_t *pipeline)
```

delete_pipeline - deletes pipeline

###### Params
- `@pipeline` pointer to pipeline

###### Returns
- 0

### 22 - ptree.c


##### Function: *ptree_new_node

```c
ptree_t *ptree_new_node(ptree_t *parent)
```

ptree_new_node - addes a new node into the tree

###### Params
- `@parent` pointer to the parent node

###### Returns
- pointer to the new child node

##### Function: *ptree_new_string_node

```c
ptree_t *ptree_new_string_node(ptree_t *parent, tokens_t *tokens,
							   unsigned int *cur_token)
```

ptree_new_string_node - inserts TOKEN_STRING type into a tree

###### Params
- `@parent` parent node
- `@tokens` tokens_t struct
- `@cur_token` current non-TOKEN_STRING token

###### Returns
- pointer to the newly created child node or root node

##### Function: delete_ptree

```c
int delete_ptree(ptree_t *node)
```

delete_ptree - cuts down the MEGA TREE

###### Params
- `@node` pointer to the root of the tree  NOTE: On a recursive rollllll

###### Returns
- 0

### 23 - stdlib_funcs.c


##### Function: _isspace

```c
char _isspace(char c)
```

_isspace - checks if input char is a space character

###### Params
- `@c` input character

###### Returns
- 1 on success, 0 on failure

##### Function: _atoi

```c
int _atoi(char *s)
```

_atoi - returns integer values from string

###### Params
- `@s` input string

###### Returns
- will return integer

##### Function: _perror

```c
void _perror(char *string)
```

_perror - custom perror

###### Params
- `@string` input error string to write to stderr

###### Returns
- void

##### Function: _memmove

```c
void _memmove(void *dest, void *src, size_t n)
```

_memmove - shifting an array

###### Params
- `@dest` dest
- `@src` source
- `@n` bytes to move

### 24 - stringsA.c


##### Function: *_strncat

```c
char *_strncat(char *dest, char *src, int n)
```

_strncat - concatenates from src string to dest string

###### Params
- `@dest` destination string
- `@src` source string
- `@n` number of bytes to concatenate

###### Returns
- pointer to destination

##### Function: _strcmp

```c
int _strcmp(const char *s1, const char *s2)
```

_strcmp - compares string

###### Params
- `@s1` first string
- `@s2` second string

###### Returns
- difference between two ascii valuves

##### Function: _strlen

```c
unsigned int _strlen(const char *str)
```

_strlen - finds and returns length of string

###### Params
- `@str` string to find length

###### Returns
- length of string

##### Function: *_strdup

```c
char *_strdup(char *str)
```

_strdup - takes a string and copies to another a new memory location

###### Params
- `@str` string to copy

###### Returns
- pointer to copied string

##### Function: _strncmp

```c
int _strncmp(char *s1, char *s2, unsigned int n)
```

_strncmp - checks if 2 strings are of equal value and length

###### Params
- `@s1` first string
- `@s2` second string
- `@n` number of bytes to compare

###### Returns
- difference of first chars of diff value or 0 on success

### 25 - stringsB.c


##### Function: *_strcpy

```c
char *_strcpy(char *dest, char *src)
```

_strcpy - copies a string from src to dest

###### Params
- `@dest` new copy of string
- `@src` the source of the copy

###### Returns
- pointer to copy

##### Function: *_strncpy

```c
char *_strncpy(char *dest, char *src, int n)
```

_strncpy - copies string from source to destination

###### Params
- `@dest` destination string
- `@src` source string to be copied
- `@n` bytes to be copied from source string

###### Returns
- destination string concatenated

##### Function: *_strcat

```c
char *_strcat(char *dest, char *src)
```

_strcat - concatenates from src string to dest string

###### Params
- `@dest` destination string
- `@src` source string

###### Returns
- pointer to destination

### 26 - stringsC.c


##### Function: replace_str

```c
void replace_str(char **old_str, char *new_str, int i, int j, int flg)
```

replace_str - replace part of string by another

###### Params
- `@old_str` string that will be modified
- `@new_str` string to be used as replacement
- `@i` starting position to replace in old_str
- `@j` ending position to replace in old_str
- `@flg` indicates if new_str should be freed

##### Function: *int_to_str

```c
char *int_to_str(unsigned int n)
```

int_to_str - convert an integer to a string

###### Params
- `@n` unsigned integer to print

###### Returns
- string with converted integer

##### Function: *_str_replace

```c
char *_str_replace(char *string, unsigned int start, unsigned int end,
				   char *rep)
```

str_replace - replaces part of a string for another

###### Params
- `@string` string to replace
- `@start` where to start
- `@end` where to end
- `@rep` string to replace with

###### Returns
- replaced string

### 27 - tokenize.c


##### Function: tokenize

```c
void tokenize(tokens_t *tokens, const char *string)
```

tokenize - tokenizes command string

###### Params
- `@tokens` tokens_t struct containing initial string and array of strings
- `@string` command string

### 28 - tokenizer.c


##### Function: init_tokens

```c
void init_tokens(tokens_t *tokens, int length)
```

init_tokens - initializes token struct

###### Params
- `@tokens` tokens struct to initialize
- `@length` length to malloc for

##### Function: is_redirection

```c
int is_redirection(int token_id)
```

is_redirection - checks if token id is a redirection

###### Params
- `@token_id` tokenid

###### Returns
- 1 if yes , 0 if no

##### Function: delete_tokens

```c
int delete_tokens(tokens_t *tokens)
```

delete_tokens - freeing tokens

###### Params
- `@tokens` tokens_t struct with tokens

###### Returns
- 0

##### Function: delete_dups

```c
void delete_dups(tokens_t *tokens)
```

delete_dups - deletes duplicate semi-colons from data

###### Params
- `@tokens` tokens_t struct

##### Function: token_classify

```c
void token_classify(tokens_t *tokens)
```

token_classify - classifies the tokens

###### Params
- `@tokens` tokens_t struct

### 29 - worker.c


##### Function: worker_execute_core

```c
pid_t worker_execute_core(arg_inventory_t *arginv)
```

worker_execute_core - this is the core execution function

###### Params
- `@arginv` arg inventory

###### Returns
- 0

##### Function: worker_execute_tree

```c
pid_t worker_execute_tree(arg_inventory_t *arginv, ptree_t *ptree,
						  unsigned int depth)
```

##### Function: worker_execute

```c
int worker_execute(arg_inventory_t *arginv)
```

worker_execute - executes background process

###### Params
- `@arginv` arginv

###### Returns
- 0 or exit

### 30 - write.c


##### Function: write_history

```c
unsigned int write_history(history_t *head)
```

write_history - writes all elemets of history to file

###### Params
- `@head` head of linked list to print

###### Returns
- number of nodes printed

##### Function: write_uint

```c
int write_uint(unsigned int n)
```

write_uint - writes unsigned integers to buffer or stdout in decimal

###### Params
- `@n` unsigned integer to write

###### Returns
- number of wrote to buffer

##### Function: _puts

```c
void _puts(char *str)
```

_puts - prints string from pointer to string

###### Params
- `@str` string to print

###### Returns
- void

##### Function: _putchar

```c
int _putchar(char c)
```

_putchar - writes the character c to stdout

###### Params
- `@c` The character to print

###### Returns
- On success 1. On error, -1 is returned, and errno is set appropriately.

##### Function: print_list

```c
size_t print_list(env_t *head)
```

print_list - prints all elements of linked list

###### Params
- `@head` head of linked list to print

###### Returns
- number of nodes printed

## License
MIT
More descriptions of your license go here if any