#include "my_shell.h"

/**
 * is_interactive - Determine if the shell is in interactive mode.
 * @info: Pointer to the information structure.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - Check if a character is a delimiter.
 * @character: The character to check.
 * @delimiter: The delimiter string.
 *
 * Return: 1 if it's a delimiter, 0 if not.
 */
int is_delimiter(char character, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == character)
			return (1);
	return (0);
}

/**
 * is_alphabetic - Check for an alphabetic character.
 * @c: The character to check.
 *
 * Return: 1 if 'c' is alphabetic, 0 otherwise.
 */
int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * string_to_integer - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if there are no num in the string, the converted num otherwise.
 */
int string_to_integer(char *s)
{
	int i, sign = 1, flag = 0, result;
	unsigned int output = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			output *= 10;
			output += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -output;
	else
		result = output;

	return (result);
}

