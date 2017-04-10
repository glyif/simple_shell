#ifndef PTREE
#define PTREE
/**
 * struct ptree - base parse tree struct
 * @left: left child node
 * @right: right child node
 * @parent: parent node
 * @token_id: id from macros
 * @strings: corresponding strings, NULL if not TOKEN_STRING
 * @stringsN: amount of strings in strings +1 (for NULL), 0 if not TOKEN_STRING
 */
typedef struct ptree
{
	struct ptree *left;
	struct ptree *right;
	struct ptree *parent;

	int token_id;
	const char **strings;
	unsigned int stringsN;
} ptree_t;
#endif
