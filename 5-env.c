#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
char *read_command(void)
{
	char *buffer = malloc(sizeof(char) * BUFFER_SIZE);

	if (buffer == NULL)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}
	if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
	{
		free(buffer);
		exit(EXIT_SUCCESS);
	}
	size_t len = strlen(buffer);

	if (len > 0 && buffer[len - 1] == '\n')
	{
		buffer[len - 1] = '\0';
	}
	return (buffer);
}
void print_environment(void)
{
	extern char **envi;
	char **env = envi;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
int main(void)
{
	char *command;

	while (1)
	{
		printf("$ ");
		command = read_command();
		if (strcmp(command, "env") == 0)
		{
			print_environment();
		}
		else if (strcmp(command, "exit") == 0)
		{
			printf("Exiting the shell...\n");
			break;
		}
		free(command);
	}
	return (0);
}
