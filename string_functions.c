#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 *
 * @s: The string whose length to check.
 *
 * Return: The integer length of the string. If @s is NULL, returns 0.
 */
int _strlen(char *s)
{
	int len = 0;

	if (!str)
		return (0);

	while (*str++)
		len++;
	return (len);
}

/**
 * _strcmp - Compares two strings lexicographically.
 *
 * @s1: First string to compare.
 * @s2: Second string to compare.
 *
 * Return: An integer less than, equal to, or greater than zero if s1 is found,
 *         respectively, to be less than, to match, or be greater than s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if substring starts with string
 * @string: string to search
 * @substring: the substring to find
 *
 * Return: address of next char of string or NULL
 */
char *starts_with(const char *string, const char *substring)
{
	while (*substring)
	{
		if (*substring++ != *string++)
		{
			return (NULL);
		}
	}
	return ((char *)string);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
	{
		dest++;
	}

	while (*src)
	{
		*dest++ = *src++;
	}

	*dest = *src;

	return (result);
}
