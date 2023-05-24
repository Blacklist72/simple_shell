#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * read_line - read a line from the user
 *
 * Return: pointer
 */
char *read_line(void)
{
	char *buffer = malloc(sizeof(char) * BUFFER_SIZE);

	fgets(buffer, BUFFER_SIZE, stdin);
	return (buffer);
}
/**
 * parse_line - arse a line to an array
 * @line: line prased
 * Return: an array
 */
char **parse_line(char *line)
{
	char **args = malloc(sizeof(char *) * BUFFER_SIZE);
	char *token = strtok(line, " \n");
	int y = 0;

	while (token != NULL)
	{
		args[y] = token;
		token = strtok(NULL, " \n");
		y++;
	}
	args[y] = NULL;
	return (args);
}
/**
 * execute_command - executes the command
 * @args: array of pointers
 */
void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) < 0)
		{
			printf("./shell: no sush file or directory %s\n", args[0]);
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
 * main - main function
 * Return: 0
 */
int main(void)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		printf("$ ");
		line = read_line();
		args = parse_line(line);
		execute_command(args);
		free(line);
		free(args);
	}
	return (0);
}
