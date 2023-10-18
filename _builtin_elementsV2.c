# include "my_shell.h"
/**
 * history - Display command history with line numbers.
 * @data: Data structure.
 *
 * Return: Always 0.
 */
int history(info_t *data)
{
	display_command_history(data->history);
	return (0);
}

/**
 * remove_alias - Remove an alias assignment.
 * @data: Data structure.
 * @str: Alias string to remove.
 *
 * Return: 0 on success, 1 on failure.
 */
int remove_alias(info_t *data, char *str)
{
	char *eq, tmp;
	int result;

	eq = find_char(str, '=');
	if (!eq)
	{
		return (1);
	}

	tmp = *eq;
	*eq = '\0';

	result = del_alias_node(&(data->aliases),
		find_alias_node(data->aliases, alias_starts_with(data->aliases, str, -1)));

	*eq = tmp;

	return (result);
}

/**
 * set_alias - Assign an alias to a string.
 * @data: Data structure.
 * @str: Alias string to assign.
 *
 * Return: 0 on success, 1 on failure.
 */
int set_alias(info_t *data, char *str)
{
	char *eq;

	eq = find_char(str, '=');
	if (!eq)
	{
		return (1);
	}

	if (!*++eq)
	{
		return (remove_alias(data, str));
	}

	remove_alias(data, str);
	return (add_alias_node_end(&(data->aliases), str, 0) == NULL);
}

/**
 * print_alias - Print an assigned alias.
 * @node: Alias node to print.
 *
 * Return: 0 on success, 1 on failure.
 */
int print_alias(list_t *node)
{
	char *eq, alias = NULL;

	if (node)
	{
		eq = find_char(node->str, '=');
		for (alias = node->str; alias <= eq; alias++)
		{
			print_char(*alias);
		}

		print_char('\'');
		print_string(eq + 1);
		print_string("'\n");
		return (0);
	}

	return (1);
}

/**
 * alias_command - Mimic the alias built-in command.
 * @data: Data structure.
 *
 * Return: Always 0.
 */
int alias_command(info_t *data)
{
	int index = 0;
	char *eq = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->aliases;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}

		return (0);
	}

	for (index = 1; data->argv[index]; index++)
	{
		eq = find_char(data->argv[index], '=');
		if (eq)
		{
			set_alias(data, data->argv[index]);
		}
		else
		{
			print_alias(find_alias_node(data->aliases,
						alias_starts_with(data->aliases, data->argv[index], '=')));
		}
	}

	return (0);
}

