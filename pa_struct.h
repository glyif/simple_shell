#ifndef PARSER_STRUCT
#define PARSER_STRUCT
#include "p_struct.h"
/**
 * struct parser - struct to parse
 * @tree: resulting parse tree
 */
typedef struct parser
{
	ptree_t *tree;
} parser_t;
#endif
