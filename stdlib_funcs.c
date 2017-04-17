#include "header.h"

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
		i = 1;
		break;
	default:
		i = 0;
		break;
	}

	return (i);
}
