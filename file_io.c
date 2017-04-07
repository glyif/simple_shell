#include "header.h"
/**
 * read_textfile - reads a text file and prints it to the POSIX stdout
 * @filename: the file
 * @letters: number of letters to print
 * Return: actual number of letters it could read and print
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	ssize_t letters2;
	char *buffer;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	buffer = malloc(sizeof(char) * letters);
	if (buffer == NULL)
		return (0);
	if (read(fd, buffer, letters) == -1)
	{
		free(buffer);
		return (0);
	}
	letters2 = _strlen(buffer);
	letters2 = write(STDOUT_FILENO, buffer, letters2);
	if (letters2 == -1)
	{
		free(buffer);
		return (0);
	}
	free(buffer);
	return (close(fd) == -1 ? -1 : letters2);
}
