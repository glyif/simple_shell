#include "header.h"

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to reallocate memory
 * @old_size: size in bytes of allocated memory
 * @new_size: newsize of memory block in bytes
 *
 * Return: void pointer to new allocation of memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;
	unsigned int i;

	if (ptr == NULL)
	{
		p = safe_malloc(new_size);
		return (p);
	}

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (old_size == new_size)
		return (ptr);

	p = safe_malloc(new_size);
	if (p == NULL)
		return (NULL);

	for (i = 0; i < old_size && i < new_size; i++)
		p[i] = ((char *)ptr)[i];

	free(ptr);

	return (p);
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
		_perror("No Memory\n");
		exit(1);
	}
	check = mem_reset(check, bytes);

	return (check);
}
