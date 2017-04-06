#ifndef BASE_STRUCTS
#define BASE_STRUCTS
/**
 * struct tokens - struct for tokenizing string
 * @data: initial string separated with '\0', hold all the tokens
 * @tokens: array of pointers pointing to different parts of the data string
 * @tokensN: amount of tokens parsed
 */
typedef struct tokens
{
	/* Do not deallocate everything from here until the full parse tree deallocation, because
	 * AST will use tokens from this structure!
	 */
	char *data;
	const char **tokens;
	unsigned int tokensN;
} tokens_t;
#endif
