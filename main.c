#include "header.h"

/**
 * buildarginv - function to build a struct of the arguments inventory
 * Return: pointer to arguments inventory struct
 */
arg_inventory_t *buildarginv(void)
{
	arg_inventory_t *arginv;
	char *file, *home, *name = "/.simple_shell_history";
	int lenhome, lenname;
	env_t *home_node;

	arginv = safe_malloc(sizeof(arg_inventory_t));
	arginv->input_commands = safe_malloc(BUFSIZE * sizeof(char));
	arginv->envlist = env_list();
	arginv->alias = alias_list();
	arginv->buflimit = BUFSIZE;
	arginv->st_mode = _filemode(STDIN_FILENO);
	arginv->last_exit_code = 0;
	arginv->last_bg_pid = -1;
	arginv->n_bg_jobs = 0;
	arginv->exit = 0;
	arginv->exit_status = 0;

	/* initialize history and history file */
	home_node = fetch_node(arginv->envlist, "HOME");
	home = home_node->val;
	lenhome = _strlen(home), lenname = _strlen(name);
	file = safe_malloc(sizeof(char) * (lenhome + lenname + 1));
	file = _strncat(file, home, lenhome);
	file = _strncat(file, name, lenname);
	arginv->history_file = file;
	arginv->history = history_list(arginv);

	load_alias(arginv);

	return (arginv);
}

/**
 * sig_handler - handles user input of ^C with the following
 * @sig: integer value of signal to change, will be SIGINT = ^C
 *
 * Return: void
 */
void sig_handler(int sig)
{
	(void) sig;
	_puts("");
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * main - custom shell
 * Return: 0
 */
int main(void)
{
	arg_inventory_t *arginv;
	int exit_status;

	arginv = buildarginv();
	signal(SIGINT, sig_handler);
	while (!arginv->exit)
	{
		if (arginv->st_mode)
			write(STDOUT_FILENO, "$ ", 2);
		if (!_getline(&arginv->input_commands, &arginv->buflimit))
			break;
		add_node_history(&arginv->history, arginv->input_commands);

		tokenize(&arginv->tokens, arginv->input_commands);

		if (arginv->tokens.tokensN > 0)
		{
			expand_bash_vars(arginv);

			if (parse(&arginv->parser, &arginv->tokens))
			{
				delete_parser(&arginv->parser);
				delete_tokens(&arginv->tokens);
				continue;
			}

			worker_execute(arginv);
			delete_parser(&arginv->parser);
		}

		mem_reset(arginv->input_commands, BUFSIZE);

		delete_tokens(&arginv->tokens);
	}
	exit_status = freeall(arginv);

	return (exit_status);
}
