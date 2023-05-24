#include "main.h"

/**
 * my_getlineHelper - getline helper function
 * @lineptr: string input
 * @n: int input
 * Return: int
 */
int my_getlineHelper(char **lineptr, size_t *n)
{
	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	return (0);
}



/**
 * my_getline - reads a line from a file stream
 * @line_ptr: pointer to the string input
 * @line_size: pointer to the size input
 * @file: file stream input
 * Return: ssize_t
 */
ssize_t my_getline(char **line_ptr, size_t *line_size, FILE *file)
{
	ssize_t bytes_read = 0;
	size_t position = 0, new_size;
	static char read_buf[READ_BUF_SIZE];
	static size_t buf_size, buf_pos;
	char *new_buffer;

	if (line_ptr == NULL || line_size == NULL || file == NULL
		|| resizeBuffer(line_ptr, line_size) == -1)
		return -1;
		
	while (1)
	{
		if (buf_pos >= buf_size)
		{
			bytes_read = read(file->_fileno, read_buf, READ_BUF_SIZE);
			if (bytes_read <= 0 && position == 0)
				return -1;
			else if (bytes_read <= 0)
				break;
			buf_size = bytes_read;
			buf_pos = 0;
		}
		
		if (position >= *line_size - 1)
		{
			new_size = *line_size * 2;
			new_buffer = realloc(*line_ptr, new_size);
			if (new_buffer == NULL)
				return -1;
			*line_ptr = new_buffer;
			*line_size = new_size;
		}
		
		(*line_ptr)[position++] = read_buf[buf_pos++];
		if ((*line_ptr)[position - 1] == '\n')
			break;
	}
	
	(*line_ptr)[position] = '\0';
	return position;
}

