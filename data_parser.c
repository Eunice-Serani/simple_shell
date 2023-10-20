/**
 * isExecutableCommand - Checks if a file is an executable command.
 * @info: The info struct.
 * @path: The file path.
 *
 * Return: 1 if executable, 0 otherwise.
 */
int isExecutableCommand(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
		return (1);

	return (0);
}

/**
 * duplicateSubstring - Duplicates characters from a substring.
 * @pathStr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: A pointer to the new buffer.
 */
char *duplicateSubstring(char *pathStr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathStr[i] != ':')
			buf[k++] = pathStr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * findCommandInPath - Finds a command in the PATH string.
 * @info: The info struct.
 * @pathStr: The PATH string.
 * @command: The command to find.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */
char *findCommandInPath(info_t *info, char *pathStr, char *command)
{
	int i = 0, currPos = 0;
	char *path;

	if (!pathStr)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (isExecutableCommand(info, command))
			return (command);
	}
	while (1)
	{
		if (!pathStr[i] || pathStr[i] == ':')
		{
			path = duplicateSubstring(pathStr, currPos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (isExecutableCommand(info, path))
				return (path);
			if (!pathStr[i])
				break;
			currPos = i;
		}
		i++;
	}
	return (NULL);
}

