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
#define TOKEN_AND        7
#define TOKEN_OR         8

/* -----environ----- */
extern char **environ;

/* ---------------main--------------- */
ssize_t _getline(char **buffer, size_t *limit);
int _filemode(int fd);
ssize_t _readline(int fd, char **buffer, size_t *limit);

/* --------- arguments inventory ---------- */
arg_inventory_t *buildarginv(void);
char *set_name(env_t *envlist, char *name);

/* ---------------execute--------------- */
pid_t execute(arg_inventory_t *arginv);
int exec_builtins(arg_inventory_t *arginv);
pid_t exec_path(char *command, arg_inventory_t *arginv);
/*void safe_dup2(int new_fd, int old_fd);*/
/* int redirect_output(arg_inventory_t *arginv, int close_dup); */
/* int redirect_input(arg_inventory_t *arginv); */

/* ---------------tokenizer--------------- */
int delete_tokens(tokens_t *tokens);
void tokenize(tokens_t *tokens, const char *string);
int is_redirection(int token_id);
void init_tokens(tokens_t *tokens, int length);
void delete_dups(tokens_t *tokens);
void token_classify(tokens_t *tokens);
void cleanup_tokens(tokens_t *tokens, unsigned int tokens_idx, char *data);

/* -------custom environ------- */
env_t *env_list(void);
char **separate_string(char *string);
unsigned int link_count(env_t *head);
char **zelda_to_ganondorf(env_t *head);
env_t *add_node_env(env_t **head, char *var, char *val);
int modify_node_env(env_t **head, char *new_var, char *new_val);
int remove_node_env(env_t **head, char *var);

/* ---------------builtin--------------- */
int _arsine(arg_inventory_t *arginv);
int _env(arg_inventory_t *arginv);
int _setenv(arg_inventory_t *arginv);
int _history(arg_inventory_t *arginv);
int _cd(arg_inventory_t *arginv);
int _alias(arg_inventory_t *arginv);
int _unalias(arg_inventory_t *arginv);
int the_help(arg_inventory_t *arginv);
int load_alias(arg_inventory_t *arginv);
int save_alias(arg_inventory_t *arginv);
int the_exit(arg_inventory_t *arginv);

/* ---------------strings--------------- */
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);
unsigned int _strlen(const char *str);
char *_strcpy(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
int _strcmp(const char *s1, const char *s2);
int _strncmp(char *s1, char *s2, unsigned int n);
int _unsetenv(arg_inventory_t *arginv);
char *_strcat(char *dest, char *src);
char *int_to_str(unsigned int n);
void replace_str(char **old_str, char *new_str, int i, int j, int flg);
char *_str_replace(char *string, unsigned int start, unsigned int end,
				   char *rep);

/* -----custom C std lib----- */
char _isspace(char c);
int _atoi(char *s);
void _perror(char *string);
void _memmove(void *dest, void *src, size_t n);
int is_uint(char *num);

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

/* -----alias----- */
int write_alias(alias_t *head);
alias_t *alias_list(void);
alias_t *add_node_alias(alias_t **head, char *alias, char *command);
int modify_node_alias(alias_t **head, char *new_var, char *new_val);
int remove_node_alias(alias_t **head, char *var);
alias_t *fetch_node_alias(alias_t *head, char *var);

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
int append_text_to_file(char *filename, char *text_content);

/* ---------------path--------------- */
int locate_path(char *path, env_t *envlist);
int cat_path(char **search_path, char *cmd);
int is_path(char *command);
int count_paths(char *path_str);
char **tokenize_path(char *path_str);
void free_paths(char **paths);

/* ---------------ptree--------------- */
ptree_t *ptree_new_node(ptree_t *parent);
ptree_t *ptree_new_string_node(ptree_t *parent, tokens_t *tokens,
							   unsigned int *cur_token);
int delete_ptree(ptree_t *node);

/* ---------------parser--------------- */
int parse_error(token_t *near);
ptree_t *parse_expr(unsigned int *ntoken, tokens_t *tokens, ptree_t *lhs,
					int min_prec);
int parse(parser_t *parser, tokens_t *tokens);
int delete_parser(parser_t *parser);
void expand_bash_vars(arg_inventory_t *arginv);
int expand_alias(arg_inventory_t *arginv);

/* ---------------worker--------------- */
unsigned int init_pipeline_count_processes(ptree_t *tree);
int init_pipeline_push_processes(pipeline_t *pipeline, ptree_t *tree);
int init_pipeline(pipeline_t *pipeline, ptree_t *ptree);
int worker_execute_core(arg_inventory_t *arginv);
int worker_execute(arg_inventory_t *arginv);
int delete_pipeline(pipeline_t *pipeline);

/* ---------------free--------------- */
int freeall(arg_inventory_t *arginv);
int free_environ(env_t *head);
int free_history(history_t *head);
int free_alias(alias_t *head);

/* ----help---- */
void h_exit(void);
void h_arsine(void);
void h_env(void);
void h_setenv(void);
void h_unsetenv(void);
void h_history(void);
void h_cd(void);
void h_alias(void);
void h_help(void);

#endif
