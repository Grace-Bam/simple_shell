#include "shell.h"

/**
 * _strncpy - Copies a string up to a specified number of characters.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 *
 * Return: A pointer to the concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int m, j;
	char *s = dest;

	m = 0;
	while (src[m] != '\0' && m < n - 1)
	{
		dest[m] = src[m];
		m++;
	}
	if (m < n)
	{
		j = m;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates two strings up to a specified number of bytes.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used.
 *
 * Return: A pointer to the concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int m, j;
	char *s = dest;

	m = 0;
	j = 0;
	while (dest[m] != '\0')
		m++;
	while (src[j] != '\0' && j < n)
	{
		dest[m] = src[j];
		m++;
		j++;
	}
	if (j < n)
		dest[m] = '\0';
	return (s);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area in s containing the character c.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
