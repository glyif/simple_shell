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
#include "structs.h"

/* MACROS */
#define BUFSIZE 1024
#define EXT_SUCCESS 0
#define EXT_FAILURE 1
#define TRUE (1 == 1)
#define FALSE (!TRUE)

/* this defines the macros for token_t struct */
#define TOKEN_STRING     0
#define TOKEN_SEMICOLON  1
#define TOKEN_PIPE       2
#define TOKEN_REWRITE    3
#define TOKEN_APPEND     4
#define TOKEN_CAT        5
#define TOKEN_BACKGROUND 6

/* environ */
extern char **environ;

/* main */
ssize_t _getline(char **buffer, size_t *limit);
arg_inventory_t *buildarginv(void);
int _filemode(int fd);

/* execute */
pid_t execute(arg_inventory_t *arginv, int pipein, int pipeout);
int exec_builtins(arg_inventory_t *arginv, int pipein, int pipeout);
pid_t exec_path(char *command, char **commands, env_t *envlist, int pipein, int pipeout);

/* tokenizer functions */
int delete_tokens(tokens_t *tokens);
int tokenize(tokens_t *tokens, const char *string);
int dump_token(tokens_t *tokens);
const char *dump_get_token_descr(int token_id);

/* linked list functions, support custom environ */
env_t *env_list(void);
unsigned int link_count(env_t *head);
char **zelda_to_ganondorf(env_t *head);
env_t *add_node_env(env_t **head, char *var);
env_t *modify_node_env(env_t **head, char *val, char *str);
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
int _strcmp(const char *s1, const char *s2);
int _spstrncmp(char *s1, char *s2, unsigned int n);

/* custom C std lib functions */
int _putchar(char c);
char _isspace(char c);

/* custom malloc, free functions */
char *mem_reset(char *str, int bytes);
void *safe_malloc(int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* history functions */
unsigned int write_history(history_t *head);
history_t *add_node_history(history_t **head, char *command);

/* file input / output functions */
ssize_t read_textfile(const char *filename, size_t letters);
int append_text_to_file(const char *filename, char *text_content);

/* path environ variable functions to find custom path */
int locate_path(char *path, env_t *envlist);
int path_match(char *path, char *str);
int cat_path(char **search_path, char *cmd);
int is_path(char *command);

/* ptree functions */
ptree_t *ptree_insert_string(ptree_t *parent, tokens_t *tokens, unsigned int *cur_token);
ptree_t *ptree_insert_token_right(ptree_t *parent, tokens_t *tokens, unsigned int *cur_token);
ptree_t *ptree_emplace_token(ptree_t *tree, tokens_t *tokens, unsigned int *cur_token);
ptree_t *ptree_get_root(ptree_t *node);
int delete_ptree(ptree_t *node);
int dump_ptree(ptree_t *ptree, unsigned int depth, int side);

/* parser */
int parse_error(const char *error, token_t *near);
int parse(parser_t *parser, tokens_t *tokens);
int delete_parser(parser_t *parser);

/* worker */
unsigned int init_pipeline_count_processes(ptree_t *tree);
int init_pipeline_push_processes(pipeline_t *pipeline, ptree_t *tree);
int init_pipeline(pipeline_t *pipeline, ptree_t *ptree);
int worker_execute_core(arg_inventory_t *arginv);
int worker_execute(arg_inventory_t *arginv);
int delete_pipeline(pipeline_t * pipeline);
#endif
