#include "header.h"

/**
 * h_alias - help function to explain how the associated function works
 */
void h_alias(void)
{
	_puts("\nUsage: $ alias [NAME]=[VALUE]");
	_puts("\tDefine or display aliases, in the form:");
	_puts("\n\talias [NAME]=[VALUE]");
}

/**
 * h_cd - help function to explain how the associated function works
 */
void h_cd(void)
{
	_puts("\nUsage: $ cd");
	_puts("\tChange the shell working directory.");
}

/**
 * h_env - help function to explain how the associated function works
 */
void h_env(void)
{
	_puts("\nUsage: $ env");
	_puts("\tDisplay all environmental variables, in the form:");
	_puts("\n\t[NAME]=[VALUE]");
}

/**
 * h_exit - help function to explain how the associated function works
 */
void h_exit(void)
{
	_puts("\nUsage: $ exit");
	_puts("\tExit the shell.");
}

/**
 * h_help - help function to explain how the associated function works
 */
void h_help(void)
{
	_puts("\nUsage: $ help [command]");
	_puts("\tDisplay information about builtin commands.");
}
