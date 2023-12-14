#include "shell.h"

/**
 * _strcpy - Copies a string.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcpy(char *dest, char *src)
{
	int m = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[m])
	{
		dest[m] = src[m];
		m++;
	}
	dest[m] = 0;
	return (dest);
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--str;
	return (result);
}

/**
 * _puts - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_putchar(str[m]);
		m++;
	}
}

/**
 * _putchar - Writes the character c to stdout.
 * @character: The character to print.
 *
 * Return: On success 1. On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char character)
{
	static int m;
	static char buffer[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH || m >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, m);
		m = 0;
	}
	if (character != BUFFER_FLUSH)
		buffer[m++] = character;
	return (1);
}
