#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
/**
 * main - Entry point
 * Description: Displays a prompt and waits for the user to type a command.
 * Return: Always 0
 */

int main(void)
{
	char input_buffer[BUFFER_SIZE];
	char prompt[] = "#cisfun$ ";

	while (1)
	{
		printf("%s", prompt);
		fflush(stdout);
		if (fgets(input_buffer, BUFFER_SIZE, stdin) == NULL)
		{
			break;
		}
		input_buffer[strcspn(input_buffer, "\n")] = '\0';
		if (strlen(input_buffer) == 0)
		{
			continue;
		}
		pid_t pid = fork();

		if (pid == -1)

		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			char *args[] = {input_buffer, NULL};

			execve(args[0], args, NULL);
			fprintf(stderr, "%s: No such file or directory\n", input_buffer);
			exit(1);
		}
		else
		{
			int stat;

			waitpid(pid, &stat, 0);
		}
	}
	return (0);
}
