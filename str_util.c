#include "my_shell.h"

/**
 * my_copy_string - Copies a string to another.
 * @destination: The destination string to copy to.
 * @source: The source string.
 * @max_chars: The maximum number of characters to copy.
 *
 * Return: The resulting concatenated string.
 */
char *my_copy_string(char *destination, char *source, int max_chars)
{
	char *result = destination;
	int i, j;

	i = 0;
	while (source[i] != '\0' && i < max_chars - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < max_chars)
	{
		j = i;
		while (j < max_chars)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * my_concatenate_strings - Concatenates two strings.
 * @first: The first string.
 * @second: The second string.
 * @max_bytes: The maximum number of bytes to use.
 *
 * Return: The resulting concatenated string.
 */
char *my_concatenate_strings(char *first, char *second, int max_bytes)
{
	char *result = first;
	int i, j;

	i = 0;
	j = 0;
	while (first[i] != '\0')
		i++;
	while (second[j] != '\0' && j < max_bytes)
	{
		first[i] = second[j];
		i++;
		j++;
	}
	if (j < max_bytes)
		first[i] = '\0';
	return (result);
}

/**
 * my_find_character - Locates a specific character in a string.
 * @input_string: The string to search within.
 * @target_character: The character to locate.
 *
 * Return: pointer to the mem area containing target char in the input string
 */
char *my_find_character(char *input_string, char target_character)
{
	do {

		if (*input_string == target_character)
			return (input_string);
	} while (*input_string++ != '\0');

	return (NULL);
}

