#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * read_line - Read the input
 *
 * Return: Pointer
 */
char *read_line(void)
{
	char *buffer = malloc(sizeof(char) * BUFFER_SIZE);

	fgets(buffer, BUFFER_SIZE, stdin);
	return (buffer);
}
/**
 * parse_line - Parse into an array of arguments
 * @line: The input line to be parsed
 *
 * Return: Array of arguments
 */
char **parse_line(char *line)
{
	char **args = malloc(sizeof(char *) * BUFFER_SIZE);
	char *tok = strtok(line, " \n");
	int u = 0;

	while (tok != NULL)
	{
		args[u] = tok;
		tok = strtok(NULL, " \n");
		u++;
	}
	args[u] = NULL;
	return (args);
}
/**
 * execute_command - Execute a command
 * @args: Array of command arguments
 */
void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) < 0)
		{
			printf("Command not found: %s\n", args[0]);
			exit(0);
		}
	}
	else if (pid < 0)
	{
		printf("Forking error\n");
	}
	else
	{
		wait(NULL);
	}
}
/**
 * main - Entry point for the shell program
 *
 * Return: Always 0
 */
int main(void)
{
	char *line;
	char **args;
	int stat = 1;

	while (stat)
	{
		printf("$ ");
		line = read_line();
		args = parse_line(line);
		if (strcmp(args[0], "exit") == 0)
		{
			printf("Exiting the shell...\n");
			stat = 0;
		}
		else
		{
			execute_command(args);
		}
		free(line);
		free(args);
	}
	return (0);
}
