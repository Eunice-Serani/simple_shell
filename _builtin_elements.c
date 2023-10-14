#include  "myshell.h"

/**
 * exit_shell - Terminate the shell with an optional exit status.
 * @shell_info: A structure holding potential arguments, maintaining
 *              a consistent function signature.
 *
 * Return: Exits the program with the specified exit status; returns 0 if
 *         shell_info->arguments[0] is not "exit".
 */
int exit_shell(shell_info_t *shell_info)
{
	int exit_status;

	if (shell_info->arguments[1])  /* Check for an exit argument */
	{
		exit_status = _convert_to_int(shell_info->arguments[1]);
		if (exit_status == -1)
		{
			shell_info->status = 2;
			display_error(shell_info, "Invalid exit status: ");
			print_string(shell_info->arguments[1]);
			print_character('\n');
			return (1);
		}
		shell_info->error_number = _convert_to_int(shell_info->arguments[1]);
		return (-2);
	}
	shell_info->error_number = -1;
	return (-2);
}
/**
 * change_current_directory - Modify the current working directory of the process.
 * @info: A structure that may contain arguments, ensuring a consistent function prototype.
 *
 * Return: Always returns 0.
 */
int change_current_directory(info_t *info)
{
	char *current_directory, *new_directory, buffer[1024];
	int change_dir_result;

	current_directory = getcwd(buffer, 1024);
	if (!current_directory)
		_puts("TODO: Handle >>getcwd<< failure error message here\n");
	if (!info->argv[1])
	{
		new_directory = _getenv(info, "HOME=");
		if (!new_directory)
			change_dir_result = /* TODO: Define behavior for this case */
				chdir((new_directory = _getenv(info, "PWD=")) ? new_directory : "/");
		else
			change_dir_result = chdir(new_directory);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_directory);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		change_dir_result = /* TODO: Define behavior for this case */
			chdir((new_directory = _getenv(info, "OLDPWD=")) ? new_directory : "/");
	}
	else
		change_dir_result = chdir(info->argv[1]);
	if (change_dir_result == -1)
	{
		print_error(info, "Unable to change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

 /**
 * display_help - Display help information.
 * @info: A structure that may contain arguments, ensuring a consistent function prototype.
 *
 * Return: Always returns 0.
 */
int display_help(info_t *info)
{
	char **argument_array;

	argument_array = info->argv;
	_puts("The 'help' function call works, but the function is not yet implemented.\n");
	if (0)
		_puts(*argument_array); /* Temporary workaround to suppress unused variable warning */
	return (0);
}
/**
 * show_history - Display the command history with line numbers.
 * @info: A structure that may contain arguments, ensuring a consistent function prototype.
 *
 * Return: Always returns 0.
 */
int show_history(info_t *info)
{
	print_command_history(info->history);
	return 0;
}
/**
 * Unset an alias by making it empty.
 *
 * @param info A data structure containing relevant information.
 * @param alias The alias to unset.
 *
 * Return: 0 on success, 1 on failure.
 */
int unset_alias(info_t *info, char *alias)
/**
 * unset_alias - Remove an alias from the list.
 * @info: A structure containing parameters.
 * @alias: The alias to be unset.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *alias)
{
	char *p = _strchr(alias, '=');
	if (!p) return 1;
	char c = *p;
	*p = 0;
	int r = delete_node_at_index(&(info->alias), get_node_index(info->alias, node_starts_with(info->alias, alias, -1)));
	*p = c;
	return r;
}
