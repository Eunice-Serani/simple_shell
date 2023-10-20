#include "my_shell.h"
/**
 *	calculate_list_length - Determines the length of a linked list.
 *	@h: Pointer to the first node.
 *
 *	Return: The size of the list.
 */
size_t calculate_list_length(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}
	return (count);
}

/**
 *	convert_list_to_string_array - Returns an array of strings from
 *	@head: Pointer to the first node.
 *
 *	Return: An array of strings.
 */
char **convert_list_to_string_array(list_t *head)
{
	list_t *node = head;
	size_t length = calculate_list_length(head);
	size_t array_index;
	char **strings;
	char *str;

	if (!head || !length)
		return (NULL);

	strings = malloc(sizeof(char *) * (length + 1));
	if (!strings)
		return (NULL);

	for (array_index = 0; node; node = node->next, array_index++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < array_index; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strings[array_index] = str;
	}
	strings[array_index] = NULL;
	return (strings);
}

/**
 *	display_list_elements - Prints all elements of a list_t linked list.
 *	@h: Pointer to the first node.
 *
 *	Return: The size of the list.
 */
size_t display_list_elements(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 *	find_node_with_prefix - Returns the node whose string starts with a prefix.
 *	@node: Pointer to the list head.
 *	@prefix: String to match.
 *	@c: The next character after the prefix to match.
 *
 *	Return: The matching node or NULL.
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 *	find_node_position - Gets the index of a node.
 *	@head: Pointer to list head.
 *	@node: Pointer to the node.
 *
 *	Return: The index of the node or -1.
 */
ssize_t find_node_position(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

