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

/* included custom headers */
#include "base_structs.h"

/* MACROS and variables */
#define BUFSIZE 1024
#define EXT_SUCCESS 0
#define EXT_FAILURE 1

extern char **environ;

/* main functions */
ssize_t _getline(char **buffer, size_t *limit);
void execute(char **commands, env_t *envlist);
int execdavinci_builtins(char** commands);

/* tokenizer functions */
int delete_tokens(tokens_t *tokens);
int tokenize(tokens_t *tokens, const char *string);

/* environ variable functions (support linked list & convert to char**) */
env_t *env_node(env_t **head, char *str);
env_t *env_list(void);
unsigned int link_count(env_t *head);
char **zelda_to_ganondorf(env_t *head);

/* builtin functions */
int builtin_exit(char **commands);
int builtin_monalisa(char **commands);

/* custom C standard library functions */
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);
char *_strdup(char *str);
unsigned int _strlen(const char *str);

/* file input / output functions */
ssize_t read_textfile(const char *filename, size_t letters);
int append_text_to_file(const char *filename, char *text_content);

/* custom malloc, free functions */
char *mem_reset(char *str, int bytes);
void *safe_malloc(int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif
