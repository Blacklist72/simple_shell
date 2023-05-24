#include "main.h"

/**
 * print_string - Print a string to standard output.
 * @str: String input.
 * Return: void
 */
void print_string(const char *str)
{
	if (!str)
		return;

	while (*str)
	{
		write(STDOUT_FILENO, str, 1);
		str++;
	}
}

/**
 * deallocate_array - Deallocate memory for an array of pointers.
 * @array: Array of pointers.
 * Return: void
 */
void deallocate_array(char **array)
{
	int i;

	if (!array)
		return;

	for (i = 0; array[i]; i++)
	{
		free(array[i]);
		array[i] = NULL;
	}

	free(array);
}

/**
 * split_string - split_string a given string by a delimiter.
 * @data: Data struct input.
 * @delimiter: String input.
 * Return: void
 */
void split_string(data *data, const char *delimiter)
{
	char *token;
	int num_tokens = 0;

	data->arguments = malloc(2 * sizeof(char *));
	if (data->arguments == NULL)
	{
		free(data->command);
		perror(data->shell_name);
		exit(EXIT_FAILURE);
	}
	data->arguments[0] = NULL;
	data->arguments[1] = NULL;

	token = strtok(data->command, delimiter);
	while (token)
	{
		data->arguments = resize_memory(data->arguments, (num_tokens + 2) * sizeof(char *));
		if (data->arguments == NULL)
			goto free_memory;
		data->arguments[num_tokens] = stringDuplicate(token);
		if (data->arguments[num_tokens] == NULL)
			goto free_memory;
		num_tokens++;
		token = strtok(NULL, delimiter);
	}
	data->arguments[num_tokens] = NULL;
	return;

free_memory:
	deallocate_array(data->arguments);
	free(data->command);
	perror(data->shell_name);
	exit(EXIT_FAILURE);
}

/**
 * initialize_data - Initialize the data structure.
 * @data: Data struct input.
 * @shell_name: String input.
 * Return: void
 */
void initialize_data(data *data, const char *shell_name)
{
	data->command = NULL;
	data->arguments = NULL;
	data->shell_name = shell_name;
	data->last_exit_status = EXIT_SUCCESS;
	data->flag_setenv = 0;
}

/**
 * read_command - Read the command from the prompt and structure it into the data struct.
 * @data: Data struct input.
 * Return: void
 */
void read_command(data *data)
{
	size_t buffer_size = 0;
	ssize_t chars_read;
	int i = 0;

	chars_read = GetLine(&data->command, &buffer_size, stdin);

	if (chars_read == -1)
	{
		free(data->command);
		exit(EXIT_SUCCESS);
	}

	data->command[chars_read - 1] = '\0';
	remove_whitespace(data->command);
	/* Replace pound sign with end of line (can also be done with strtok) */
	for (i = 0; data->command[i] != '\0'; i++)
	{
		if (data->command[i] == '#')
		{
			data->command[i] = '\0';
			break;
		}
	}
	remove_whitespace(data->command);
}
