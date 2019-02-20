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

/**
 * _atoi - returns integer values from string
 * @s: input string
 *
 * Return: will return integer
 */
int _atoi(char *s)
{
	int result = 0, sign = 0, c;

	for (c = 0; s[c] != '\0'; c++)
	{
		if (s[c] == '-')
			sign++;
		if (s[c] > 47 && s[c] < 58)
		{
			while (s[c] > 47 && s[c] < 58)
				result = result * 10 - (s[c++] - 48);
			break;
		}
	}
	return (result *= sign % 2 == 0 ? -1 : 1);
}

/**
 * _perror - custom perror
 * @string: input error string to write to stderr
 *
 * Return: void
 */
void _perror(char *string)
{
	unsigned int len;

	len = _strlen(string);

	write(STDERR_FILENO, string, len);
}

/**
 * _memmove - shifting an array
 * @dest: dest
 * @src: source
 * @n: bytes to move
 */
void _memmove(void *dest, void *src, size_t n)
{
	char *copy_source, *copy_dest, *temp;
	size_t i;

	copy_source = (char *)src;
	copy_dest = (char *)dest;
	temp = malloc(sizeof(char) * 1024);

	for (i = 0; i < n; i++)
		temp[i] = copy_source[i];

	for (i = 0; i < n; i++)
		copy_dest[i] = temp[i];
	free(temp);
}

/**
 * is_uint - checks if input string is unsigned int
 * @num: the input number
 * Return: TRUE or FALSE
 */
int is_uint(char *num)
{
	int i = 0;

	while (num[i])
	{
		if (num[i] > 47 && num[i] < 58)
			i++;
		else if (num[i] == 45 && i == 0)
			return (FALSE);
		else
			return (FALSE);
	}

	return (TRUE);
}
