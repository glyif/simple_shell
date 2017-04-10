#ifndef T_STRUCT
#define T_STRUCT
/**
 * struct token - categorizes a token
 * @id: id of token from TOKEN_ macros
 * @str: token
 */
typedef struct token
{
        int id;
        const char *str;
} token_t;

/**
 * struct tokens - struct for tokenizing string
 * @data: initial string separated with '\0', hold all the tokens
 * @tokens: array of token_t structs with tokenized strings and ids
 * @tokensN: amount of tokens parsed
 *
 * NOTE: do not deallocate everthing from here until the full parse tree
 * deallocation, because AST will use tokens from this structure!
 */
typedef struct tokens
{
        char *data;
        token_t *tokens;
        unsigned int tokensN;
} tokens_t;

/**
 * struct token_id
 * @token_id: numerical id
 * @token_str: the exact token string to be compared with
 * @token_descr: for debugging
 */
typedef struct token_id
{
	int token_id;
	const char *token_str;
	const char *token_descr;
} token_types;
#endif
