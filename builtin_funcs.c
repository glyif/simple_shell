#include "header.h"

/**
 * builtin_exit - exits daVinci
 * @commands - input commands, not used in this function
 *
 * Return: 0 on success
 */
int builtin_exit(char **commands)
{
	(void)commands;

	write(STDOUT_FILENO, "Simplicity is the ultimate sophistication\n", 42);
	exit(EXT_SUCCESS);
}

/**
 * builtin_monalisa - prints mona lisa ascii art
 * @commands - input commands, not used in this function
 *
 * Return: 0 on success
 */
int builtin_monalisa(char **commands)
{
	(void)commands;

	if (!read_textfile("monalisa.txt", 3808))
		write(STDOUT_FILENO, "Simplicity is the ultimate sophistication\n", 42);

	return (0);
}
