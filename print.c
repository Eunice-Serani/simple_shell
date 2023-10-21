#include "shell.h"

/**
 * _write - prints string to standard output
 * @str: string to print
 *
 * Return: number of characters printed
 */
int _write(char *str)
{
	return (write(STDOUT_FILENO, str, _strlen(str)));
}

/**
 * _ewrite - prints errors to standard error
 * @err: string to print
 *
 * Return: number of characters printed
 */
int _ewrite(char *err)
{
	return (write(STDERR_FILENO, err, _strlen(err)));
}
