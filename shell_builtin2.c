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
	_setenv(data, "PWD", cwd);
	if (!dir)
		dir = _getenv("HOME");
	if (chdir(dir) == -1)
		perror("cd");
	else
	{
		_setenv(data, "OLDPWD", _getenv("PWD"));
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");
		_setenv(data, "PWD", cwd);
	}
}
