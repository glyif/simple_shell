#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

/*included standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "base_structs.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* MACROS and variables */
#define BUFSIZE 1024
extern char **environ;

/* main functions */
int _getline(char *buffer, int limit);

/* tokenizer functions */
int tokenize(tokens_t *tokens, const char *string);

/* environ variable functions (support linked list & convert to char**) */
env_t *env_node(env_t **head, char *str);
env_t *env_list(void);
unsigned int link_count(env_t *head);
char **zelda_to_ganondorf(env_t *head);

/* custom C standard library functions */
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);
char *_strdup(char *str);
unsigned int _strlen(const char *str);

/* custom malloc, free functions */
char *mem_reset(char *str, int bytes);
void *safe_malloc(int size);
#endif
