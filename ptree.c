#include "header.h"
/**
 * ptree_insert_string - inserts TOKEN_STRING type into a tree
 * @parent: parent node
 * @tokens: tokens_t struct
 * @cur_token: current non-TOKEN_STRING token
 *
 * NOTE: This function is built to be run in a while loop not recurssively.
 * Return: pointer to the newly created child node (orrrr root node if root doesn't exist)
 */
ptree_t *ptree_insert_string(ptree_t *parent, tokens_t *tokens, unsigned int *cur_token)
{
	unsigned int i;
	unsigned int start, finish;
	ptree_t *node;

	/* Base Case: stops at a string or runs out of arguments */
	if ((*cur_token >= tokens->tokensN) || (tokens->tokens[*cur_token].id != TOKEN_STRING))
		return (NULL);

	/* check if right child is occupied */
	if (parent && parent->right)
	{
		perror("Right child is already occupied.\n");
		return (NULL);
	}

	node = safe_malloc(sizeof(ptree_t));

	if (!node)
	{
		perror("Memory allocation failed\n");
		exit(1); /* done messed up */
	}

	node->left = NULL;
	node->right = NULL;
	node->parent = parent;

	/* point parent right to newly created node (SUPER IMPORTANT) */
	if (parent)
		parent->right = node;

	/* We need to know how many more strings are after the current token */
	start = *cur_token;

	/* shifting cur_token to next non-TOKEN_STRING token */
	while ((*cur_token < tokens->tokensN) && (tokens->tokens[*cur_token].id == TOKEN_STRING))
		(*cur_token)++;

	finish = *cur_token;

	/* We now know how pointers to strings we need to malloc for */
	/* Initialize everything else */
	node->token_id = TOKEN_STRING;
	node->stringsN = finish - start;
	node->strings = safe_malloc((node->stringsN + 1) * sizeof(const char *));

	if (!node->strings)
	{
		perror("Memory allocation failed\n");
		exit(1);
	}

	/* initialize stringsssssssss */
	for (i = 0; i < node->stringsN; i++)
		node->strings[i] = tokens->tokens[i + start].str;

	node->strings[i] = NULL;

	return (node);
}

/**
 * ptree_emplace_token - emplaces a token in place of another
 *
 * Description: this function is super important!
 * This function eplaces a token in place of another which becomes it's left child
 * Left childs will not have any other children. This way we are able to know
 * how many commands there are in a complex command.
 *
 * @tree: pointer to tree
 * @tokens: tokens_t struct
 * @cur_token: current non-TOKEN_STRING token
 *
 * NOTE: This function is built to be run in a while loop not recurssively.
 * Return: pointer to new node
 */
ptree_t *ptree_emplace_token(ptree_t *tree, tokens_t *tokens, unsigned int *cur_token)
{
	int origin;
	token_t *token;
	ptree_t *parent, *current, *new_node;

	/* Base Case: stops at a string or runs out of arguments */
	if (!tree || (*cur_token >= tokens->tokensN) || (tokens->tokens[*cur_token].id == TOKEN_STRING))
		return (NULL);

	/* Fetch pointer to the token to be emplaced */
	token = tokens->tokens + *cur_token;
	(*cur_token)++;

	/* Fetch all the needed data */
	parent = tree->parent;
	current = tree;

	/* if -1, we are replacing left element from parent node */
	/* if 1, we are replacing right element from parent node */
	/* if 0, parent is NULL so we don't need to do anything */
	if (!parent)
		origin = 0;
	else if (parent->left == current)
		origin = -1;
	else
		origin = 1;

	/* Allocate memory for new dnoe and initialize it */
	new_node = safe_malloc(sizeof(ptree_t));

	if (!new_node)
	{
		perror("Memory allocation failed\n");
		exit(1); /* you done messed up */
	}

	/* you might need to draw this out...... */
	/* but basically, this is adding a node in between a child and a parent */
	new_node->left = current;
	new_node->right = NULL;
	new_node->parent = parent;

	new_node->token_id = token->id;
	new_node->strings = NULL;
	new_node->stringsN = 0;

	/* Rebuild the tree */
	if (origin < 0)
		parent->left = new_node;
	else if (origin > 0)
		parent->right = new_node;

	current->parent = new_node;

	return (new_node);
}

/* this function is temp, should be removed..... does the same but inserts to right instead of left
 * sort of a duplicate of ptree_insert_string */
ptree_t *ptree_insert_token_right(ptree_t *parent, tokens_t *tokens, unsigned int *cur_token)
{
	ptree_t *node;
	token_t *token;

	if ((*cur_token >= tokens->tokensN) || (tokens->tokens[*cur_token].id == TOKEN_STRING))
		return (NULL);

	if (parent && parent->right)
	{
		perror("Right child is already occupied.");
		return (NULL);
	}

	node = safe_malloc(sizeof(ptree_t));

	if (!node)
	{
		perror("Memory allocation failed\n");
		exit(1);
	}

	node->left = NULL;
	node->right = NULL;
	node->parent = parent;

	if (parent)
		parent->right = node;

	token = tokens->tokens + *cur_token;
	(*cur_token)++;

	node->token_id = token->id;
	node->stringsN = 0;
	node->strings = NULL;

	return (node);
}

/**
 * ptree_get_root - finds the root node. ALL THE WAY UP MORTY. FIND THE MEGA ROOT OF THE MEGA TREE.
 * @node: pointer to a node of a tree
 *
 * Return: Pointer to the root node of a tree
 */
ptree_t *ptree_get_root(ptree_t *node)
{
	/* traverse and navigate up the MEGA TREE to get to the MEGA ROOT */
	while (node->parent)
		node = node->parent;

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
