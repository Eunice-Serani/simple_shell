#include "my_shell.h"

/**
 * my_strlen - Calculate string length.
 * @s: String to measure.
 * Return: Length of the string as an integer.
 */
int my_strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * my_strcmp - Compare two strings lexicographically.
 * @s1: First string.
 * @s2: Second string.
 * Return: Negative if s1 < s2, positive if s1 > s2, or zero if s1 == s2.
 */
int my_strcmp(char *s1, char *s2)
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
 * starts_with - Check if needle starts with haystack.
 * @h: String to search.
 * @n: Substring to find.
 * Return: Address of the next character of haystack or NULL.
 */
char *starts_with(const char *h, const char *n)
{
	while (*n)
		if (*n++ != *h++)
			return (NULL);
	return ((char *)h);
}

/**
 * my_strcat - Concatenate two strings.
 * @d: Destination buffer.
 * @s: Source buffer.
 * Return: Pointer to the destination buffer.
 */
char *my_strcat(char *d, char *s)
{
	char *r = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (r);
}

