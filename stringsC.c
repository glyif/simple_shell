#include "header.h"

/**
 * replace_str - replace part of string by another
 *
 * @old_str: string that will be modified
 * @new_str: string to be used as replacement
 * @i: starting position to replace in old_str
 * @j: ending position to replace in old_str
 * @flg: indicates if new_str should be freed
 *
 */
void replace_str(char **old_str, char *new_str, int i, int j, int flg)
{
	char *tmp;

	tmp = _str_replace(*old_str, i, j, new_str);
	free(*old_str);
	*old_str = tmp;
	if (flg)
		if (new_str[0])
			free(new_str);
}

/**
 * separate_string - separates string at first '='
 * @string: one string from environ or alias input
 *
 * Return: array of 2 strings
 */
char **separate_string(char *string)
{
	char **result, *left, *right;
	int i, j, lenleft = 0, lenright = 0;

	while (string[lenleft] != '=')
		lenleft++;
	left = safe_malloc(sizeof(char) * lenleft + 1);

	for (i = 0; i < lenleft; i++)
		left[i] = string[i];

	i = lenleft + 1;

	while (string[i] != '\0')
		lenright++, i++;
	right = safe_malloc(sizeof(char) * lenright + 1);

	for (i = lenleft + 1, j = 0; j < lenright; i++, j++)
		right[j] = string[i];

	result = safe_malloc(sizeof(char *) * 3);
	result[0] = left, result[1] = right;

	return (result);
}

/**
 * int_to_str - convert an integer to a string
 * @n: unsigned integer to print
 * Return: string with converted integer
 */
char *int_to_str(unsigned int n)
{
	unsigned int copy, size;
	int nth, chars_written;
	char *str;
	int  chars;

	size = 1;
	chars_written = 0;
	copy = n;

	if (n < 10)
	{
		str = safe_malloc(2);
		str[0] = ('0' + n);
		return (str);
	}

	chars = 0;
	while (copy / 10 != 0)
	{
		copy /= 10, size *= 10;
		chars++;
	}

	str = safe_malloc(chars + 2);
	while (size > 0)
	{
		nth = n / size;
		str[chars_written] = ('0' + nth);
		n -= nth * size;
		size /= 10;
		chars_written++;
	}
	str[chars_written] = '\0';
	return (str);
}

/**
 * str_replace - replaces part of a string for another
 * @string: string to replace
 * @start: where to start
 * @end: where to end
 * @rep: string to replace with
 *
 * Return: replaced string
 */
char *_str_replace(char *string, unsigned int start, unsigned int end,
				   char *rep)
{
	char *new_str;

	new_str = safe_malloc(_strlen(string) + _strlen(rep) + 1);

	_strncpy(new_str, string, start);

	_strcat(new_str, rep);

	if (end < _strlen(string) - 1)
		_strcat(new_str, &string[end + 1]);

	return (new_str);
}
