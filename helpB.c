#include "header.h"

/**
 * h_history - help function to explain how the associated function works
 */
void h_history(void)
{
	_puts("\nUsage: $ history");
	_puts("Display the history list.");
}

/**
 * h_arsine - help function to explain how the associated function works
 */
void h_arsine(void)
{	_puts("\nUsage: $ arsine");
	_puts("\t shows chemical formula of shell");
}

/**
 * h_setenv - help function to explain how the associated function works
 */
void h_setenv(void)
{
	_puts("\nUsage: $ setenv [NAME] [VALUE]");
	_puts("\tSets a new environmental variable");
}

/**
 * h_unsetenv - help function to explain how the associated function works
 */
void h_unsetenv(void)
{
	_puts("\nUsage: $ unsetenv [NAME]");
	_puts("\tUnsets a saved environmental variable");
}
