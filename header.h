#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "base_structs.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFSIZE 1024
extern char **environ;
int tokenize(tokens_t *tokens, const char *string);
env_t *env_list(void);
char *_strdup(char *str);
unsigned int _strlen(const char *str);
char *mem_reset(char *str, int bytes);
void *safe_malloc(int size);
unsigned int link_count(env_t *envp);
char **zelda_to_ganondorf(env_t *envp);
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);
#endif
