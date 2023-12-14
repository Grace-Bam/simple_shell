#include "shell.h"

/**
 * mem_set - Fills a memory area with a constant byte.
 *
 * @s: Pointer to the memory area.
 * @b: Byte to fill *s with.
 * @n: Number of bytes to be filled.
 *
 * Return: A pointer to the memory area s.
 */
char *mem_set(char *s, char b, unsigned int n)
{
	unsigned int m;

	for (m = 0; m < n; m++)
		s[m] = b;
	return (s);
}

/**
 * free_f - Frees a string of strings.
 *
 * @str_array: String of strings.
 */
void free_f(char **str_array)
{
	char **arr_ptr = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(arr_ptr);
}

/**
 * re_alloc - Reallocates a block of memory.
 *
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the old memory block.
 */
void *re_alloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
