#include "main.h"

/**
 * launch_process - Launch a new process.
 * @data_struct: Data struct input.
 * Return: void
 */
void launch_process(data *data_struct)
{
	pid_t proc_id = fork();
	int proc_status = 0;

	if (proc_id == -1)
		goto cleanup;
	if (proc_id == 0 && execve(data_struct->av[0], data_struct->av, NULL) == -1)
		goto cleanup;
	else if (wait(&proc_status) == -1)
		goto cleanup;
	if (WIFEXITED(proc_status))
		data_struct->last_exit_status = WEXITSTATUS(proc_status);
	return;
cleanup:
	perror(data_struct->shell_name);
	deallocate_array(data_struct->av);
	free(data_struct->cmd);
	exit(EXIT_FAILURE);
}

/**
 * signal_handler - Signal handler function.
 * @signal_num: Signal number input.
 * Return: void
 */
void signal_handler(int signal_num)
{
	/*const char prompt[] = PROMPT;*/
	(void)signal_num;
	exit(EXIT_FAILURE);
	/*print_string(prompt);*/
}

/**
 * execute_command - Execute a command.
 * @data_struct: Data struct input.
 * Return: void
 */
void execute_command(data *data_struct)
{
	const char prompt[] = PROMPT;

	signal(SIGINT, signal_handler);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_string(prompt);

		read_command(data_struct);
		if (stringLength(data_struct->cmd) != 0)
		{
			split_string(data_struct, " ");
			if (!execute_builtin(data_struct))
			{
				locateExecutable(data_struct);
				if (access(data_struct->av[0], F_OK) == -1)
				{
					perror(data_struct->shell_name);
				}
				else
				{
					launch_process(data_struct);
				}
			}
			deallocate_array(data_struct->av);
		}
		free(data_struct->cmd);
	}
}
