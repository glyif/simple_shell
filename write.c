#include "header.h"

/**
 * write_history - writes all elemets of history to file
 * @head: head of linked list to print
 *
 * Return: number of nodes printed
 */
unsigned int write_history(history_t *head)
{
	unsigned int i = 0;

	while (head)
	{
		write_uint(head->number);
		write(STDOUT_FILENO, "  ", 2);
		write(STDOUT_FILENO, head->command, _strlen(head->command));
		head = head->next;
		i++;
	}

	return (i);
}

/**
 * write_uint - writes unsigned integers to buffer or stdout in decimal
 * @n: unsigned integer to write
 * Return: number of wrote to buffer
 */
int write_uint(unsigned int n)
{
	unsigned int copy, size;
	int nth, chars_written = 0;

	size = 1;
	copy = n;
	if (n < 10)
	{
		_putchar('0' + n);
		return (1);
	}
	while (copy / 10 != 0)
		copy /= 10, size *= 10;
	while (size > 0)
	{
		nth = n / size;
		_putchar('0' + nth);
		n -= nth * size;
		size /= 10;
		chars_written++;
	}
	return (chars_written);
}

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
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * print_list - prints all elements of linked list
 * @head: head of linked list to print
 *
 * Return: number of nodes printed
 */
size_t print_list(env_t *head)
{
	unsigned int i = 0;
	char **_environ;

	_environ = zelda_to_ganondorf(head);

	while (_environ[i])
	{
		_puts(_environ[i]);
		free(_environ[i]);
		i++;
	}

	free(_environ);
	return (i);
}
