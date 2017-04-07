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
 * mem_reset - sets all bytes of string to '\0'
 * @str: string
 * @bytes: number of bytes
 *
 * Return: pointer to string with reset mem
 */
char *mem_reset(char *str, int bytes)
{
	int i = 0;

	while (i < bytes)
		str[i++] = '\0';

	return (str);
}

/**
 * safe_malloc - mallocs memory of size bytes, prints error message on error
 * @bytes: number of bytes to malloc
 *
 * Return: pointer to malloced memory or NULL
 */
void *safe_malloc(int bytes)
{
	void *check;

	check = malloc(bytes);
	if (check == NULL)
	{
		perror("No Memory");
		return (check);
	}
	check = mem_reset(check, bytes);

	return (check);
}

/**
 * _strncpy - copies a string to another string
 * @dest: destination string
 * @src: source string to be copied
 * @n: number of bytes to be copied
 *
 * Return: pointer to copied string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;
	int j = 0;

	while (src[i] != '\0')
		i++;

	while (j < n && src[j] != '\0')
	{
		dest[j] = src[j];
		j++;
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
