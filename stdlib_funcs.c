#include "header.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _isspace - checks if input char is a space character
 * @c: input character
 *
 * Return: 1 on success, 0 on failure
 */
char _isspace(char c)
{
	int i;

	switch (c)
	{
	case ' ': case '\t': case '\n':
	case '\v': case '\f': case '\r':
	case ':':
		i = 1;
		break;
	default:
		i = 0;
		break;
	}

	return (i);
}
