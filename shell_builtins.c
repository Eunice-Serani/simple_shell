#include "shell.h"

/**
 * print_env - prints environment variables
 */
void print_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		_write(environ[i]);
		_write("\n");
		i++;
	}
}

/**
 * is_builtin - checks and executes builtin functions
 * @data: contains program info
 * @pg_name: name of the program
 *
 * Return: 1 if it command matches inbuilt command
 */
int is_builtin(data_t *data, char *pg_name)
{
	int status = 0;

	if (_strcmp(data->cmd_args[0], "exit") == 0)
	{
		if (data->cmd_args[1])
		{
			status = _atoi(data->cmd_args[1]);
			if (status == -1)
			{
				errno = 2;
				_print_atoi_error(data, pg_name);
				data->process_no += 1;
				free_array(data->cmd_args);
				return (1);
			}
			free(data->buffer);
			free_array(data->cmd_args);
			exit(status % 256);
		}
		free(data->buffer);
		free_array(data->cmd_args);
		exit(errno);
	}
	if (_strcmp(data->cmd_args[0], "env") == 0)
	{
		print_env();
		free_array(data->cmd_args);
		data->process_no += 1;
		status = 1;
	}
	return (status);
}
