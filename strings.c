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
 * _strncpy - copies a string to another string
 * @dest: destination string
 * @src: source string to be copied
 * @n: number of bytes to be copied
 *
 * Return: pointer to copied string
 */
char *_strncpy(char *dest, char *src, int n, int start)
{
	int i = 0;
	int j = 0;

	while (src[i] != '\0')
		i++;

	while (j < n && src[start] != '\0')
	{
		dest[j] = src[start];
		j++;
		start++;
	}

	while (n > i)
		dest[i++] = '\0';


	return (dest);
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

char _isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	if (c == ':')
		return (1);

	return (0);
}

/**
 * _strcpy - copy string
 * @dest: copy of src
 * @src: the source of the copy
 *
 * Return: the copy of the src
 */

char *_strcpy(char *dest, char *src)
{
	char *temp = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	return (temp);
}

/**
 * _strncat - cats from src to dest
 * @dest: destination
 * @src: source
 * @n: number of bytes
 * Return: pointer to dest
 */

char *_strncat(char *dest, char *src, int n)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
	{
	}
	j = 0;
	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
