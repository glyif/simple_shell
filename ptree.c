#include "header.h"

/**
 * ptree_new_node - addes a new node into the tree
 * @parent: pointer to the parent node
 *
 * Return: pointer to the new child node
 */
ptree_t *ptree_new_node(ptree_t *parent)
{
	ptree_t *node = safe_malloc(sizeof(ptree_t));

	node->left = NULL;
	node->right = NULL;
	node->parent = parent;
	node->strings = NULL;
	node->stringsN = 0;

	return (node);
}

/**
 * ptree_new_string_node - inserts TOKEN_STRING type into a tree
 * @parent: parent node
 * @tokens: tokens_t struct
 * @cur_token: current non-TOKEN_STRING token
 *
 * Return: pointer to the newly created child node (orrrr root node if root doesn't exist)
 */
ptree_t *ptree_new_string_node(ptree_t *parent, tokens_t *tokens, unsigned int *cur_token)
{
	unsigned int i;
	unsigned int start, finish;
	ptree_t *node;

	/* checks if the current token is a string or if we've run out of tokens */
	if ((*cur_token >= tokens->tokensN) || (tokens->tokens[*cur_token].id != TOKEN_STRING))
		return (NULL);

	node = ptree_new_node(parent);

	/* calculate number of strings after this token */
	start = *cur_token;

	while ((*cur_token < tokens->tokensN) && (tokens->tokens[*cur_token].id == TOKEN_STRING))
		(*cur_token)++;

	finish = *cur_token;

	/* We now know how pointers to strings we need to malloc for */
	/* Initialize everything else */
	node->token_id = TOKEN_STRING;
	node->stringsN = finish - start;
	node->strings = safe_malloc((node->stringsN + 1) * sizeof(const char *));


	/* initialize stringsssssssss */
	for (i = 0; i < node->stringsN; i++)
		node->strings[i] = tokens->tokens[i + start].str;

	node->strings[i] = NULL;

	return (node);
}


/**
 * delete_ptree - cuts down the MEGA TREE
 * @node: pointer to the root of the tree
 *
 * NOTE: On a recursive rollllll
 * Return: 0
 */
int delete_ptree(ptree_t *node)
{
	/* Base case: when node is NULL */
	if (!node)
		return (0);

	/* Recussively delete child nodes */
	delete_ptree(node->left);
	delete_ptree(node->right);

	/* free strings */
	if(node->strings)
		free(node->strings);

	/* delete input node (could be root node, could be some child node) */
	free(node);
	return (0);
}

/**
 * dump_ptree - prints parse MEGA TREE
 * @ptree: pointer to root node
 * @depth: how deep to print
 * @side: left or right child
 * side < 0 is left child
 * side > 0 is right child
 * side 0 is root
 *
 * NOTE: recusion yet again
 * Return: 0
 */
int dump_ptree(ptree_t *ptree, unsigned int depth, int side)
{
	unsigned int i;
	/* Base Case: when ptree == NULL */
	if (!ptree)
		return (0);

	/* Print current part of ptree depending on depth and side */
	for (i = 0; i < depth; i++)
		putchar('|');

	/* Print side sign */
	if (side < 0)
		putchar('<');
	else if (side > 0)
		putchar('>');
	else
		putchar('#');

	if (ptree->token_id == TOKEN_STRING)
	{
		for (i = 0; i < ptree->stringsN; i++)
			printf(" %s", ptree->strings[i]);
		printf("\n");
	}
	else
	{
		printf(" - %s token\n", dump_get_token_descr(ptree->token_id));
	}

	/* recursively call on all left and right childs */
	dump_ptree(ptree->left,  depth + 1, -1);
	dump_ptree(ptree->right, depth + 1, 1);

	return (0);
}
