#include "shell.h"

/**
 * exec_cmd - executes the command
 * @data: contains program info
 * @argv: array of arguments supplied to the program
 */
void exec_cmd(data_t *data, char **argv)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror(argv[0]);
		exit(-1);
	}
	if (child_pid == 0)
	{
		execve(data->cmd_args[0], data->cmd_args, environ);
		perror(argv[0]);
		exit(2);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
		}
		errno = status;
		free_array(data->cmd_args);
	}
}
