#include "main.h"

/**
 * execute_builtin - Check if it is a built-in command and then execute it.
 * @data: Data structure input.
 * Return: 1 if it is a built-in command, 0 if not.
 */
int execute_builtin(data *data)
{
	builtin builtins[] = {
		{"exit", exit_builtin},
		{"show_env", env_builtin},
		{"set_env", setenv_builtin},
		{"unset_env", unsetenv_builtin},
		{"change_dir", cd_builtin},
		{NULL, NULL},
	};
	int index = 0;

	for (index = 0; builtins[index].cmd; index++)
	{
		if (stringCompare(data->arguments[0], builtins[index].cmd) == 0)
		{
			builtins[index].func(data);
			return (1);
		}
	}
	return (0);
}

/**
 * exit_builtin - Exit the shell.
 * @data: Data structure input.
 * Return: void
 */
void exit_builtin(data *data)
{
	if (data->arguments[1] && isNumber(data->arguments[1]))
		data->exit_status = atoi(data->arguments[1]);
	deallocate_array(data->arguments);
	free(data->command);
	if (data->flag_setenv)
		deallocate_array(environ);
	exit(data->exit_status);
}

/**
 * env_builtin - Print the current environment.
 * @data: Data structure input.
 * Return: void
 */
void env_builtin(data *data)
{
	int i = 0;

	(void)data;
	while (environ[i])
	{
		print_string(environ[i]);
		print_string("\n");
		i++;
	}
}

/**
 * setenv_builtin - Initialize a new environment var
 * or modify the existing one.
 * @data: Data structure input.
 * Return: void
 */
void setenv_builtin(data *data)
{
	(void)data;
	if (data->arguments[1] && data->arguments[2])
	{
		if (setEnv(data, data->arguments[1], data->arguments[2]) == -1)
		{
			perror("setenv");
		}
	}
}

/**
 * unsetenv_builtin - Remove an environment variable.
 * @data: Data structure input.
 * Return: void
 */
void unsetenv_builtin(data *data)
{
	int i, j;
	int len;

	(void)data;
	if (!data->arguments[1] || !getenv(data->arguments[1]))
	{
		display_error(data->shell_name, "variable not found.");
		return;
	}
	len = strlen(data->arguments[1]);
	for (i = 0; environ[i]; i++)
		if (strncmp(environ[i], data->arguments[1], len) == 0 && environ[i][len] == '=')
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
}
