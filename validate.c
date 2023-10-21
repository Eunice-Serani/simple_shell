#include "shell.h"

/**
 * check_cmd - validates user commands
 * @data: contains program data
 * @argv: array of arguments supplied to the program
 *
 * Return: 1 if the command is valid, otherwise 0
 */
int check_cmd(data_t *data, char **argv)
{
	if (access(data->cmd_args[0], X_OK) == -1)
	{
		char *full_path = search_path(data->cmd_args[0]);

		if (full_path != NULL)
		{
			free(data->cmd_args[0]);
			data->cmd_args[0] = full_path;
			return (1);
		}
		else
		{
			_print_error(data, argv[0]);
			free_array(data->cmd_args);
			return (0);
		}
	}

	return (1);
}
