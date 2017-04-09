#include "header.h"
/**
 * _puts - prints string from pointer to string
 * @str: string to print
 *
 * Return: void
 */
void _puts(char *str)
{
	write(STDOUT_FILENO, str, _strlen(str));
	_putchar('\n');
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
