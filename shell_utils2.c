#include "main.h"

/**
 * display_error - Print an error message to stderr.
 * @program_name: Name of the program.
 * @error_msg: Error message string.
 * Return: void
 */
void display_error(const char *program_name, const char *error_msg)
{
	if (!program_name || !error_msg)
		return;

	while (*program_name)
	{
		write(STDERR_FILENO, program_name, 1);
		program_name++;
	}

	write(STDERR_FILENO, ": ", 2);

	while (*error_msg)
	{
		write(STDERR_FILENO, error_msg, 1);
		error_msg++;
	}

	write(STDERR_FILENO, "\n", 1);
}

/**
 * remove_whitespace - Remove leading and trailing spaces and tabs from the string.
 * @str_input: String input.
 * Return: void.
 */
void remove_whitespace(char *str_input)
{
	int index, target_index, length = stringLength(str_input);

	for (index = 0; index < length && (str_input[index] == ' ' || str_input[index] == '\t'); index++)
		;

	for (target_index = 0; index < length ; index++, target_index++)
		str_input[target_index] = str_input[index];

	str_input[target_index] = '\0';

	for (index = stringLength(str_input) - 1; index > 0 && (str_input[index] == ' ' || str_input[index] == '\t'); index--)
		str_input[index] = '\0';
}

/**
 * resize_memory - Reallocates a memory block using malloc and free.
 * @ptr_input: Pointer to the memory block.
 * @new_size: New size of the memory block.
 * Return: Pointer to the newly allocated memory.
 */
void *resize_memory(void *ptr_input, unsigned int new_size)
{
	char *new_ptr;
	unsigned int i, copy_size = new_size, old_size = sizeof(ptr_input);

	if (old_size == new_size)
		return ptr_input;

	if (ptr_input == NULL)
		return malloc(new_size);

	if (new_size > old_size)
		copy_size = old_size;

	if (new_size == 0)
	{
		free(ptr_input);
		return NULL;
	}

	new_ptr = malloc(new_size);

	for (i = 0; i < copy_size; i++)
		new_ptr[i] = ((char *)ptr_input)[i];

	free(ptr_input);
	return new_ptr;
}
