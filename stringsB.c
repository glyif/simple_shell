#include "header.h"

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
 * _strcat - concatenates from src string to dest string
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to destination
 */
char *_strcat(char *dest, char *src)
{
	while (*dest)
		dest++;

	while (*src)
		*(dest++) = *(src++);

	*dest = '\0';

	return (dest);
}
