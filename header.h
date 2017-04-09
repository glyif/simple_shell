#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

/* included standard library headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>

/* included custom headers */
#include "base_structs.h"

/* MACROS and variables */
#define BUFSIZE 1024
#define EXT_SUCCESS 0
#define EXT_FAILURE 1

extern char **environ;

/* main functions */
ssize_t _getline(char **buffer, size_t *limit);
void execute(arg_inventory_t *arginv);
int exec_builtins(arg_inventory_t *arginv);
arg_inventory_t *buildarginv(void);
int is_path(char *command);
void exec_path(char *command, char **commands, env_t *envlist);

/* tokenizer functions */
int delete_tokens(tokens_t *tokens);
int tokenize(tokens_t *tokens, const char *string);

/* linked list functions, support custom environ */
env_t *env_node(env_t **head, char *str);
env_t *env_list(void);
unsigned int link_count(env_t *head);
char **zelda_to_ganondorf(env_t *head);
env_t *add_node_end(env_t **head, char *var);
env_t *modify_node(env_t **head, char *val, char *str);
size_t print_list(env_t *head);

/* builtin functions */
int the_exit(arg_inventory_t *arginv);
int _monalisa(arg_inventory_t *arginv);
int _env(arg_inventory_t *arginv);
int _setenv(arg_inventory_t *arginv);

/* string functions */
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);
unsigned int _strlen(const char *str);
char *_strcpy(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
int _strncmp(char *s1, char *s2, unsigned int n);
void _puts(char *str);

/* custom C std lib functions */
int _putchar(char c);
char _isspace(char c);

/* custom malloc, free functions */
char *mem_reset(char *str, int bytes);
void *safe_malloc(int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* file input / output functions */
ssize_t read_textfile(const char *filename, size_t letters);
int append_text_to_file(const char *filename, char *text_content);

/* path environ variable functions to find custom path */
int locate_path(char *path, env_t *envlist);
int path_match(char *path, char *str);
int cat_path(char **search_path, char *cmd);

#endif
