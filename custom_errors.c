#include "shell.h"

/**
 * custom_puts - Prints an input string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void custom_puts(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		custom_putchar(str[m]);
		m++;
	}
}

/**
 * custom_putchar - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar(char c)
{
	static int m;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || m >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, m);
		m = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[m++] = c;
	return (1);
}

/**
 * custom_putfd - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int custom_putfd(char c, int fd)
{
	static int m;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || m >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, m);
		m = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[m++] = c;
	return (1);
}

/**
 * custom_putsfd - Prints an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int custom_putsfd(char *str, int fd)
{
	int m = 0;

	if (!str)
		return (0);
	while (*str)
	{
		m += custom_putfd(*str++, fd);
	}
	return (m);
}
