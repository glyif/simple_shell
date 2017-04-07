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
	char **tokens;
	unsigned int tokensN;
} tokens_t;

/**
 * struct env - struct for holding a env var
 * @var: env var
 * @next: pointer to the next env node
 */
typedef struct env
{
	char *var;
	struct env *next;
} env_t;
#endif
