#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to the destination string
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[i] != '\0')
	{
		i++;
	}

	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}

	dest[i + j] = '\0';
	return (dest);
}

/**
 * _strcpy - copies a string to another string
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to the destination string
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * split_string - splits string into tokens
 * @buffer: string to split
 * @split_con: delimiter
 *
 * Return: Array of splitted parts terminated by a NULL pointer
 */
char **split_string(char *buffer, char *split_con)
{
	char *buf = NULL;
	char **parts = NULL;
	int i = 0;

	if (buffer == NULL)
	{
		return (NULL);
	}

	parts = malloc(sizeof(char *) * MAX_ARGS);
	if (parts == NULL)
	{
		return (NULL);
	}
	buf = strtok(buffer, split_con);

	while (buf != NULL && i < MAX_ARGS - 1)
	{
		parts[i] = _strdup(buf);
		buf = strtok(NULL, split_con);
		i++;
	}
	parts[i] = NULL;

	return (parts);
}

/**
 * _strcmp - compares two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: 0 if the strings are similar
 */
int _strcmp(char *str1, char *str2)
{
	int i;
	int len;
	int result = 0;

	if (_strlen(str1) >= _strlen(str2))
	{
		len = _strlen(str1);
	}
	else
	{
		len = _strlen(str2);
	}

	for (i = 0; i < len; i++)
	{
		if (str1[i] == str2[i])
		{
			continue;
		}
		else
		{
			result = str1[i] - str2[i];
			break;
		}
	}

	return (result);
}
