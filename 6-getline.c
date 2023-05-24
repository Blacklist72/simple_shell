#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
/**
 * custom_getline - Read input from stdin using a getline function
 *
 * Return: Pointer to the input, or NULL
 */
char *custom_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int index;
	static int size;
	char *line = NULL;
	int u = 0;
	char y = 0;

	index = 0;
	size = 0;
	while (1)
	{
		if (index >= size)
		{
			size = read(0, buffer, BUFFER_SIZE);
			index = 0;
			if (size <= 0)
			{
				return (NULL);
			}
		}
		y = buffer[index];
		index++;
		if (y == '\n' || y == EOF)
		{
			break;
		}
		line = realloc(line, (u + 1) * sizeof(char));
		line[u] = y;
		u++;
	}
	line = realloc(line, (u + 1) * sizeof(char));
	line[u] = '\0';
	return (0);
}
/**
 * main - Entry point
 *
 * Return: 0
 */
int main(void)
{
	char *line;

	while ((line = custom_getline()) != NULL)
	{
		printf("Input: %s\n", line);
		free(line);
	}
	return (0);
}
