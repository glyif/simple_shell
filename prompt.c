#include "header.h"

/**
 * print_prompt - prints custom prompt with pwd
 * @envlist: envlist
 */
void print_prompt(env_t *envlist)
{
	env_t *pwd;
	int len;
	char *prompt;

	pwd = fetch_node(envlist, "PWD");
	len = _strlen(pwd->val);
	prompt = safe_malloc(sizeof(char) * len + 4);

	prompt = _strncpy(prompt, "$ ", 2);
	prompt = _strncat(prompt, pwd->val, len + 1);
	prompt = _strncat(prompt, " ", 1);
	
	write(1, prompt, len + 4);
	free(prompt);
}
