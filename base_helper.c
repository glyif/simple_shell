#include "header.h"

/**
 * _strlen - gets length of string
 * @str: string
 *
 * Return: length
 */
unsigned int _strlen(const char *str)
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
        ;

    return (i);
}

/**
 * mem_reset - sets all bytes to '\0'
 * @str: string
 * @bytes: number of bytes
 *
 * Return: pointer to reset mem
 */
char *mem_reset(char *str, int bytes)
{
    int i;

    i = 0;
    while (i < bytes)
    {
        str[i] = '\0';
        i++;
    }

    return (str);
}

/**
 * safe_malloc - mallocs that checks if is memory is there and clears
 * @size
 *
 * Return: pointer to malloced memory
 */
void *safe_malloc(int size)
{
	void *check;

	check = malloc(size);
	if (check == NULL)
	{
		perror("No Memory");
		return (check);
	}
	check = mem_reset(check, size);

	return (check);
}

/**
 * _strncpy - copies a string
 * @dest: destination
 * @src: source
 * @n: max characters copied
 *
 * Return: copied string
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
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}

/**
 * _strdup - takes a string and copies to another place and returns pointer to it
 * @str: stirng
 *
 * Return: pointer to string
 */
char *_strdup(char *str)
{
	unsigned int len, j;
	char *ptrstring;

	if (str == NULL)
		return (NULL);

	len = _strlen(str);

	ptrstring = safe_malloc(len * sizeof(char));

	for (j = 0; j < len; j++)
		ptrstring[j] = str[j];

	return (ptrstring);
}
