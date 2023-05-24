#include "main.h"

/**
 * Getline_HelperFunc - Helper function for reading a line
 * @line: Pointer to the line buffer
 * @size: Pointer to the line buffer size
 * Return: 0 on success, -1 on failure
 */
int Getline_HelperFunc(char **line, size_t *size)
{
	if (*line == NULL || *size == 0)
	{
		*size = 128;
		*line = malloc(*size);
		if (*line == NULL)
			return (-1);
	}
	return (0);
}

/**
 * GetLine - Reads a line from the specified file stream
 * @line: Pointer to the line buffer
 * @size: Pointer to the line buffer size
 * @stream: File stream to read from
 * Return: Number of characters read (including the newline character),
 *         -1 on failure or end-of-file condition
 */
ssize_t GetLine(char **line, size_t *size, FILE *stream)
{
	ssize_t bytesRead = 0;
	size_t position = 0, newSize;
	static char buf[READ_BUF_SIZE];
	static size_t bufSize, bufPos;
	char *newBuffer;

	if (line == NULL || size == NULL || stream == NULL
		|| Getline_HelperFunc(line, size) == -1)
		return (-1);

	while (1)
	{
		if (bufPos >= bufSize)
		{
			bytesRead = read(stream->_fileno, buf, READ_BUF_SIZE);
			if (bytesRead <= 0 && position == 0)
				return (-1);
			else if (bytesRead <= 0)
				break;
			bufSize = bytesRead;
			bufPos = 0;
		}

		if (position >= *size - 1)
		{
			newSize = *size * 2;
			newBuffer = realloc(*line, newSize);
			if (newBuffer == NULL)
				return (-1);
			*line = newBuffer;
			*size = newSize;
		}

		(*line)[position++] = buf[bufPos++];

		if ((*line)[position - 1] == '\n')
			break;
	}

	(*line)[position] = '\0';
	return (position);
}
