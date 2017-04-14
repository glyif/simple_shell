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
#include <signal.h>

/* included custom headers */
#include "structs.h"

/* -----MACROS----- */
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

/* -----environ----- */
extern char **environ;

/* ---------------main--------------- */
ssize_t _getline(char **buffer, size_t *limit);
arg_inventory_t *buildarginv(void);
int _filemode(int fd);

/* ---------------execute--------------- */
pid_t execute(arg_inventory_t *arginv, int pipein, int pipeout);
int exec_builtins(arg_inventory_t *arginv, int pipein, int pipeout);
pid_t exec_path(char *command, char **commands, env_t *envlist, int pipein, int pipeout);

/* ---------------tokenizer--------------- */
int delete_tokens(tokens_t *tokens);
int tokenize(tokens_t *tokens, const char *string);
int dump_token(tokens_t *tokens);
const char *dump_get_token_descr(int token_id);

/* -------custom environ------- */
env_t *env_list(void);
char **separate_env(char *string);
unsigned int link_count(env_t *head);
char **zelda_to_ganondorf(env_t *head);
env_t *add_node_env(env_t **head, char *var, char *val);
int modify_node_env(env_t **head, char *new_var, char *new_val);
int remove_node_env(env_t **head, char *var);

/* ---------------builtin--------------- */
int the_exit(arg_inventory_t *arginv);
int _monalisa(arg_inventory_t *arginv);
int _env(arg_inventory_t *arginv);
int _setenv(arg_inventory_t *arginv);
int _history(arg_inventory_t *arginv);
int _cd(arg_inventory_t *arginv);

/* ---------------strings--------------- */
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);
unsigned int _strlen(const char *str);
char *_strcpy(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
int _strcmp(const char *s1, const char *s2);
int sp_strncmp(char *s1, char *s2, unsigned int n);
int _unsetenv(arg_inventory_t *arginv);

/* -----custom C std lib----- */
char _isspace(char c);

/* ---------------custom malloc--------------- */
char *mem_reset(char *str, int bytes);
void *safe_malloc(int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* ---------------history--------------- */
history_t *history_list(arg_inventory_t *arginv);
history_t *add_node_history(history_t **head, char *command);
int file_history(arg_inventory_t *arginv);
char *history_to_string(history_t *head);
history_t *init_history(history_t *head, char *buffer);

/* ---------------cd--------------- */
char *yellow_brick_road(char **commands, env_t *envlist);
env_t *fetch_node(env_t *head, char *var);

/* ---------------write--------------- */
int write_uint(unsigned int n);
unsigned int write_history(history_t *head);
void _puts(char *str);
size_t print_list(env_t *head);
int _putchar(char c);

/* ---------------file I/O--------------- */
ssize_t read_textfile(char *filename, size_t letters);
int trunc_text_to_file(char *filename, char *text_content);

/* ---------------path--------------- */
int locate_path(char *path, env_t *envlist);
int cat_path(char **search_path, char *cmd);
int is_path(char *command);

/* ---------------ptree--------------- */
ptree_t *ptree_insert_string(ptree_t *parent, tokens_t *tokens, unsigned int *cur_token);
ptree_t *ptree_insert_token_right(ptree_t *parent, tokens_t *tokens, unsigned int *cur_token);
ptree_t *ptree_emplace_token(ptree_t *tree, tokens_t *tokens, unsigned int *cur_token);
ptree_t *ptree_get_root(ptree_t *node);
int delete_ptree(ptree_t *node);
int dump_ptree(ptree_t *ptree, unsigned int depth, int side);

/* ---------------parser--------------- */
int parse_error(const char *error, token_t *near);
int parse(parser_t *parser, tokens_t *tokens);
int delete_parser(parser_t *parser);

/* ---------------worker--------------- */
unsigned int init_pipeline_count_processes(ptree_t *tree);
int init_pipeline_push_processes(pipeline_t *pipeline, ptree_t *tree);
int init_pipeline(pipeline_t *pipeline, ptree_t *ptree);
int worker_execute_core(arg_inventory_t *arginv);
int worker_execute(arg_inventory_t *arginv);
int delete_pipeline(pipeline_t * pipeline);

/* ---------------free--------------- */
int freeall(arg_inventory_t *arginv);
int free_environ(env_t *head);
int free_history(history_t *head);

#endif
