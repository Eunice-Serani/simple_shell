#include "_v2shell.h"

/**
 * ssize_t readAndBufferInput(data_t *data
 *   char **buffer, size_t *length) - Read
 * data from the specified buffer and return
 * @param data: Structure.
 * @param buffer: Address of the buffer.
 * @param length: Address of the length variable.
 *
 * Return: Bytes read.
 */
ssize_t readAndBufferInput(data_t *data, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t lenPos = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handleSigint);
		bytesRead = getline(buffer, &lenPos, stdin);
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			data->lineCountFlag = 1;
			removeComments(*buffer);
			buildHistoryList(data, *buffer, data->historyCount++);
			*length = bytesRead;
			data->commandBuffer = buffer;
		}
	}
	return (bytesRead);
}

/**
 * processInput - Read and buffer input, handling chained commands.
 * @data: Relevant structure.
 *
 * Return: The number of bytes read.
 */
ssize_t processInput(data_t *data)
{
	static char *buf;
	static size_t i = 0;
	ssize_t r = 0;
	char **b = &(data->args);
	char *p;

	_putchar(BUF_FLUSH);
	r = inputBuffer(data, &buf);

	if (r == -1)
		return (-1);

	if (buf)
	{
		p = buf + i;
		i = getNextCmdIndex(data, buf, i);

		if (!buf[i])
		{
			i = 0;
			data->cmdType = CMD_NORMAL;
		}

		*b = p;
		return (getCmdLength(p));
	}

	*b = buf;
	return (r);
}
/**
 * readBuffer - Read a buffer.
 * @d: Relevant parameters.
 * @b: Buffer to read into.
 * @n: Address of size variable.
 *
 * Return: Number of bytes read.
 */
ssize_t readBuffer(data_t *d, char *b, size_t *n)
{
	ssize_t r = 0;

	if (*n)
		return (0);

	r = read(d->readFd, b, READ_BUFFER_SIZE);

	if (r >= 0)
		*n = r;

	return (r);
}

/**
 * readLine - Read the next line of input.
 * @d: Parameter struct.
 * @b: Address of a buffer, preallocated or NULL.
 * @n: Size of the preallocated buffer if not NULL.
 *
 * Return: Number of characters read.
 */
int readLine(data_t *d, char **b, size_t *n)
{
	static char inBuf[READ_BUF_SIZE];
	static size_t i = 0, len = 0;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *b;
	if (p && n)
		s = *n;
	if (i == len)
		i = len = 0;

	r = readBuffer(d, inBuf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(inBuf + i, '\n');
	k = c ? 1 + (unsigned int)(c - inBuf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);

	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, inBuf + i, k - i);
	else
		_strncpy(new_p, inBuf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (n)
		*n = s;
	*b = p;
	return (s);
}
/**
 * sigintHandler - Ctrl-C signal handler.
 * @sig: Signal number (unused).
 */
void sigintHandler(int sig)
{
	_puts("\n$ ");
	_putchar(BUF_FLUSH);
}
