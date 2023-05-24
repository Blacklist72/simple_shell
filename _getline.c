#include "main.h"

/**
 * _getline_helper - getline helper function
 * @lineptr: string input
 * @n: int input
 * Return: int
 */
int _getline_helper(char **new_lineptr, size_t *new_n)
{
	if (*new_lineptr == NULL || *new_n == 0)
	{
		*new_n = 128;
		*new_lineptr = malloc(*new_n);
		if (*new_lineptr == NULL)
			return -1;
	}

	return 0;
}


/**
 * _getline - reads the input from FILE
 * @lineptr: string input
 * @n: int input
 * @stream: FILE input
 * Return: ssize_t
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t bytes_read = 0;
	size_t position = 0, new_size;
	static char buffer[READ_BUF_SIZE];
	static size_t buffer_size, buffer_pos;
	char *new_buffer;

	if (lineptr == NULL || n == NULL || stream == NULL || _getline_helper(lineptr, n) == -1)
		return -1;

	while (1)
	{
		if (buffer_pos >= buffer_size)
		{
			bytes_read = read(stream->_fileno, buffer, READ_BUF_SIZE);
			if (bytes_read <= 0 && position == 0)
				return -1;
			else if (bytes_read <= 0)
				break;
			buffer_size = bytes_read;
			buffer_pos = 0;
		}
		if (position >= *n - 1)
		{
			new_size = *n * 2;
			new_buffer = realloc(*lineptr, new_size);
			if (new_buffer == NULL)
				return -1;
			*lineptr = new_buffer;
			*n = new_size;
		}
		(*lineptr)[position++] = buffer[buffer_pos++];
		if ((*lineptr)[position - 1] == '\n')
			break;
	}
	(*lineptr)[position] = '\0';

	return position;
}
