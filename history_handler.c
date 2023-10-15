#include "_v2shell.h"

/**
 * historyFilePath - Get the history file path.
 * @info: Pointer to the parameter structure.
 *
 * Return: Allocated string with the history file path.
 */
char *historyFilePath(info_t *info)
{
	char *dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);

	size_t len = _strlen(dir) + _strlen(HIST_FILE) + 2;
	char *buf = malloc(len);
	if (!buf)
		return (NULL);

	_sprintf(buf, "%s/%s", dir, HIST_FILE);
	return (buf);
}
/**
 * saveHistory - Store history in a file.
 * @info: Parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int saveHistory(info_t *info)
{
	char *filename = historyFilePath(info);

	if (!filename)
		return (-1);

	int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	list_t *node = info->history;
	while (node)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}
/**
 * _rdhistory - Reads and updates the history list from a file.
 * @info: Parameter struct.
 *
 * Return: the number of history entries read, or 0 on failure.
 */
int _rdhistory(info_t *info)
{
	int linecount = 0;
	char *file = get_history_file(info);
	if (!file)
		return (0);

	int fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		return (0);

	struct stat st;
	if (!fstat(fd, &st) && st.st_size > 1)
	{
		char *buf = malloc(st.st_size + 1);
		if (buf)
		{
			ssize_t rd = read(fd, buf, st.st_size);
			if (rd > 0)
			{
				buf[st.st_size] = '\0';
					close(fd);

					int last = 0;
					for (int i = 0; i <= st.st_size; i++)
					{
						if (i == st.st_size || buf[i] == '\n')
						{
							buf[i] = '\0';
							build_history_list(info, buf + last, linecount++);
							last = i + 1;
						}
					}

					free(buf);
					info->histcount = linecount;

					while (info->histcount >= HIST_MAX)
					{ 
						delete_node_at_index(&(info->history), 0);
						info->histcount--;
					}

					renumber_history(info);
					return (info->histcount);
			}
			free(buf);
		}
	}

	close(fd);
	return (0);
}

/**
 * add_history_entry - Appends a history entry to the linked list.
 * @info: Parameter struct.
 * @entry: History entry string.
 * @linecount: Line count of the history entry.
 *
 * Return: 0 on success.
 */
int add_history_entry(info_t *info, char *entry, int linecount)
{
	list_t *node = info->history;

	while (node && node->next)
		node = node->next;

	add_node_end(&node, entry, linecount);
	info->history = (info->history) ? info->history : node;

	return (0);
}

/**
 * update_history_numbers - Updates the history entry numbers.
 * @info: Parameter struct.
 *
 * Return: the new histcount.
 */
int update_history_numbers(info_t *info)
{
	list_t *node = info->history;
	int count = 0;

	while (node)
	{
		node->num = count++;
		node = node->next;
	}

	return (info->histcount = count);
}
