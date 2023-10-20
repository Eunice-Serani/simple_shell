#include "my_shell.h"

/**
 * string_to_int - Converts a string to an integer
 * @s: The string to be converted
 *
 * Return: The converted integer, or -1 on error
 */
int string_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error_message - Prints an error message
 * @info: The info struct containing information
 * @error_str: String containing the specific error type
 */
void print_error_message(info_t *info, char *error_str)
{
	print_to_stderr(info->filename);
	print_to_stderr(": ");
	print_integer(info->line_count, STDERR_FILENO);
	print_to_stderr(": ");
	print_to_stderr(info->argv[0]);
	print_to_stderr(": ");
	print_to_stderr(error_str);
}

/**
 * print_integer - Prints an integer to a file descriptor
 * @input: The integer to print
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters printed
 */
int print_integer(int input, int fd)
{
	int (*put_char_func)(char) = write_char_to_stdout;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		put_char_func = write_char_to_stderr;

	if (input < 0)
	{
		absolute_value = -input;
		put_char_func('-');
		count++;
	}
	else
		absolute_value = input;

	current = absolute_value;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			put_char_func('0' + current / i);
			count++;
		}
		current %= i;
	}
	put_char_func('0' + current);
	count++;

	return (count);
}

/**
 * convert_to_string - Converts a number to a string
 * @num: The number to convert
 * @base: The base for conversion
 * @flags: Flags for formatting
 *
 * Return: The converted string
 */
char *convert_to_string(long int num, int base, int flags)
{
	static char *digits;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long value = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		value = -num;
		sign = '-';
	}

	digits = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = digits[value % base];
		value /= base;
	} while (value != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comment - Replaces the first instance of '#' with '\0'
 * @buffer: Address of the string to modify
 */
void remove_comment(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
	}
}

