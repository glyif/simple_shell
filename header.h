#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "base_structs.h"
int tokenize(tokens_t *tokens, const char *string);
#endif
