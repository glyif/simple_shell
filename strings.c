#include "header.h"

/**
 * _strlen - finds and returns length of string
 * @str: string to find length
 *
 * Return: length of string
 */
unsigned int _strlen(const char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;

	return (i);
}

/**
 * _strdup - takes a string and copies to another a new memory location
 * @str: string to copy
 *
 * Return: pointer to copied string
 */
char *_strdup(char *str)
{
	unsigned int len, j;
	char *ptrstring;

	if (str == NULL)
		return (NULL);

	len = _strlen(str);

	ptrstring = safe_malloc((len + 1) * sizeof(char));

	for (j = 0; j < len; j++)
		ptrstring[j] = str[j];
	ptrstring[j] = '\0';

	return (ptrstring);
}

/**
 * _strcmp - checks if 2 strings are of equal value and length
 * @s1: destination string
 * @s2: source string to be compared
 *
 * Return: difference of first characters that are of diff value or 0 on success
 */
int _strcmp(char *s1, char *s2)
{
	int j;

	for (j = 0; s1[j] != '\0' && s2[j] != '\0'; j++)
		if (s1[j] != s2[j])
			return (s1[j] - s2[j]);

	return (0);
}

/**
 * _strcpy - copies a string from src to dest
 * @dest: new copy of string
 * @src: the source of the copy
 *
 * Return: pointer to copy
 */
char *_strcpy(char *dest, char *src)
{
	int c;

	for (c = 0; src[c] != '\0'; c++)
		dest[c] = src[c];

	dest[c] = '\0';

	return (dest);
}

/**
 * _strncpy - copies string from source to destination
 * @dest: destination string
 * @src: source string to be copied
 * @n: bytes to be copied from source string
 *
 * Return: destination string concatenated
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j;

	for (j = 0; j < n && src[j] != '\0'; j++)
		dest[j] = src[j];

	while (j < n)
	{
		dest[j] = '\0';
		j++;
	}

	return (dest);
}

/**
 * _strncat - concatenates from src string to dest string
 * @dest: destination string
 * @src: source string
 * @n: number of bytes to concatenate
 *
 * Return: pointer to destination
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0, j = 0;

	while (dest[i] != '\0')
		i++;

	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';

	return (dest);
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
	case ' ':
	case '\t':
	case '\n':
	case '\v':
	case '\f':
	case '\r':
	case ':':
		i = 1;
		break;
	default:
		i = 0;
		break;
	}

	return (i);
}
