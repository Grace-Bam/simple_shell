#include "shell.h"

/**
 * _str_to_int - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted number, 0 if no numbers in the string, -1 on error.
 */
int _str_to_int(char *s)
{
	int m = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (m = 0;  s[m] != '\0'; m++)
	{
		if (s[m] >= '0' && s[m] <= '9')
		{
			result *= 10;
			result += (s[m] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * display_error - Prints an error message.
 * @info: The parameter & return info struct.
 * @estr: String containing specified error type.
 *
 * Return: Nothing.
 */
void display_error(info_t *info, char *estr)
{
	custom_puts(info->fname);
	custom_puts(": ");
	display_int(info->line_count, STDERR_FILENO);
	custom_puts(": ");
	custom_puts(info->argv[0]);
	custom_puts(": ");
	custom_puts(estr);
}

/**
 * display_int - Prints a decimal (integer) number (base 10).
 * @input: The input integer.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int display_int(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int m, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = custom_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (m = 1000000000; m > 1; m /= 10)
	{
		if (_abs_ / m)
		{
			__putchar('0' + current / m);
			count++;
		}
		current %= m;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_to_string - Converts a number to a string using the specified base.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags for customization.
 *
 * Return: A string representation of the number.
 */
char *convert_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
