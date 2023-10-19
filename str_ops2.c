#include "my_shell.h"

/**
 * my_copy_string - Copy a string.
 * @destination: The destination string.
 * @source: The source string.
 *
 * Return: Pointer to the destination string.
 */
char *my_copy_string(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = 0;
	return (destination);
}

/**
 * my_string_duplicate - Duplicate a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *my_string_duplicate(const char *str)
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
 * my_print_string - Print an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void my_print_string(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		my_putchar(str[index]);
		index++;
	}
}

/**
 * my_putchar - Write a character to stdout.
 * @c: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_putchar(char c)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || index >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}
	if (c != FLUSH_BUFFER)
		buffer[index++] = c;
	return (1);
}

