#include "shell.h"

/**
 * main - UNIX command line interpreter
 * @argc: number of arguments supplied
 * @argv: list of arguments supplied
 *
 * Return: 0 (Success)
 */
int main(int argc, char **argv)
{
	data_t data = DATA_INIT;
	int pip_check = isatty(STDIN_FILENO);

	(void) argc;
	errno = 0;
	while (1)
	{
		data.process_no += 1;
		if (pip_check)
			_write(PROMPT);
		data.bytes_read = getline(&data.buffer, &data.buffer_length, stdin);
		if (data.bytes_read == -1)
		{
			free(data.buffer);
			break;
		}
		data.cmd_args = split_string(data.buffer, " \t\n");
		if (data.cmd_args[0] == NULL)
		{
			free(data.cmd_args);
			continue;
		}

		if (is_builtin(&data, argv[0]))
			continue;
		if (!check_cmd(&data, argv))
		{
			free(data.buffer);
			data.buffer = NULL;
			data.process_no += 1;
			errno = 127;
			continue;
		}
		exec_cmd(&data, argv);
	}
	return (errno);
}
