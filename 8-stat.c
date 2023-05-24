#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64
#define PATH_DELIMITER ":"

extern char **environ;

char *get_command_path(char *command, char *path)
{
	return (NULL);
}
int execute_command(char **args)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	if (pid == 0)
	{
		execv(args[0], args);
		perror("execv error");
		exit(1);
	}
	else
	{
		int stat;

		waitpid(pid, &stat, 0);
		return (WEXITSTATUS(stat));
	}
}
int split_input(char *input, char **args)
{
	return (0);
}
void exit_shell(int stat)
{
	printf("Exiting the shell...\n");
	exit(stat);
}
void print_environment(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
int main(void)
{
	char input[MAX_INPUT_LENGTH];
	char *args[MAX_ARGS];
	char *path = getenv("PATH");

	while (1)
	{
		printf("$ ");
		fflush(stdout);
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		if (strcmp(input, "exit") == 0)
		{
			exit_shell(0);
		}
		else if (strncmp(input, "exit ", 5) == 0)
		{
			int status = atoi(input + 5);

			exit_shell(status);
		}
		else if (strcmp(input, "env") == 0)
		{
			print_environment();
		}
		else
		{
			int arg_count = split_input(input, args);

			if (arg_count > 0)
			{
				char *command_path = get_command_path(args[0], path);

				if (command_path != NULL)
				{
					args[0] = command_path;
					execute_command(args);
					free(command_path);
				}
				else
				{
					printf("Command not found: %s\n", args[0]);
				}
			}
		}
	}
	return (0);
}
