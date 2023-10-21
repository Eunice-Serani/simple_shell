#include "my_shell.h"

/**
 * shell_loop - Main shell loop.
 * @info: Pointer to information structure.
 * @av: Argument vector from main().
 *
 * Return: 0 on success, 1 on error, or an error code.
 */
int shell_loop(info_t *info, char **av)
{
	ssize_t read_result = 0;
	int builtin_result = 0;

	while (read_result != -1 && builtin_result != -2)
	{
		clear_info(info);
		if (is_interactive(info))
			my_print_string("$ ");
		my_putchar(FLUSH_BUFFER);
		read_result = get_user_input(info);
		if (read_result != -1)
		{
			set_info(info, av);
			builtin_result = find_builtin_command(info);
			if (builtin_result == -1)
				find_executable_command(info);
		}
		else if (is_interactive(info))
			my_putchar('\n');
		free_info(info, 0);
	}
	write_shell_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin_command - Locate a builtin command.
 * @info: Pointer to information structure.
 *
 * Return: -1 if the builtin is not found,
 *         0 if the builtin executed successfully,
 *         1 if the builtin was found but not successful,
 *         -2 if the builtin signals an exit().
 */
int find_builtin_command(info_t *info)
{
	int i, builtin_result = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (my_string_compare(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			builtin_result = builtintbl[i].func(info);
			break;
	}
	return (builtin_result);
}

/**
 * find_executable_command - Locate an executable command in PATH.
 * @info: Pointer to information structure.
 *
 * Return: void
 */
void find_executable_command(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_executable_path(info, my_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_executable_command(info);
	}
	else
	{
		if ((is_interactive(info) || my_getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_valid_command(info, info->argv[0]))
			fork_executable_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_executable_command - Fork an exec thread to run a command.
 * @info: Pointer to information structure.
 *
 * Return: void
 */
void fork_executable_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

