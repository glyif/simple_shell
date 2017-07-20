#include "header.h"

/**
 * buildarginv - function to build a struct of the arguments inventory
 * Return: pointer to arguments inventory struct
 */
arg_inventory_t *buildarginv(void)
{
	arg_inventory_t *arginv;

	arginv = safe_malloc(sizeof(arg_inventory_t));
	arginv->input_commands = safe_malloc(BUFSIZE * sizeof(char));
	arginv->envlist = env_list();
	arginv->buflimit = BUFSIZE;
	arginv->st_mode = _filemode(STDIN_FILENO);
	arginv->last_bg_pid = -1;
	arginv->n_bg_jobs = 0;
	arginv->exit = 0;
	arginv->exit_status = 0;

	/* initialize history and history file */
	arginv->history_file = set_name(arginv->envlist, "/.simple_shell_history");
	arginv->history = history_list(arginv);

	/* initialize the aliases and alias file */
	arginv->alias_file = set_name(arginv->envlist, "/.simple_shell_alias");
	arginv->alias = alias_list();
	load_alias(arginv);

	return (arginv);
}

/**
 * set_name - appends home directory absolure path to filename
 * @envlist: the linked list to environ variables
 * @name: the name of the file to be written
 *
 * Return: char pointer to filename
 */
char *set_name(env_t *envlist, char *name)
{
	char *file, *home;
	int lenhome, lenname;
	env_t *home_node;

	home_node = fetch_node(envlist, "HOME");
	home = home_node->val;

	lenhome = _strlen(home);
	lenname = _strlen(name);

	file = safe_malloc(sizeof(char) * (lenhome + lenname + 1));
	file = _strncat(file, home, lenhome);
	file = _strncat(file, name, lenname);

	return (file);
}
