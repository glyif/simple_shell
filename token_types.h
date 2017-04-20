#ifndef TOKEN_TYPES
#define TOKEN_TYPES
#include "structs.h"

token_types token_names[] = {
	{ TOKEN_SEMICOLON,  ";",  "semicolon",  1 },
	{ TOKEN_BACKGROUND, "&",  "background", 1 },
	{ TOKEN_AND,        "&&", "and",        2 },
	{ TOKEN_OR,         "||", "or",         2 },
	{ TOKEN_PIPE,       "|",  "pipe",       3 },
	{ TOKEN_REWRITE,    ">",  "rewrite",    4 },
	{ TOKEN_APPEND,     ">>", "append",     4 },
	{ TOKEN_CAT,        "<",  "cat",        4 },
	{ 9, '\0', '\0', 9}
};
#endif
