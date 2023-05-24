#include "main.h"

/**
 * builtin_change_directory - Change the current directory.
 * @data: Data structure input.
 * Return: void
 */
void builtin_change_directory(data *data)
{
	char *dir = data->arguments[1];
	char cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	setEnv(data, "PWD", cwd);
	if (!dir)
		dir = getenvValue("HOME");
	if (chdir(dir) == -1)
		perror("cd");
	else
	{
		setEnv(data, "OLDPWD", getenvValue("PWD"));
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");
		setEnv(data, "PWD", cwd);
	}
}
