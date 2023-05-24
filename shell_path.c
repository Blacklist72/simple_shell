#include "main.h"

/**
 * getenvValue - Retrieves the value of an environment variable.
 * @name: String input
 * Return: Value of the environment variable
 */
char *getenvValue(char *name)
{
	int i = -1;
	size_t name_len;

	if (name == NULL || *name == '\0')
		return (NULL);
	if (environ == NULL)
		return (NULL);

	name_len = strlen(name);

	while (environ[++i])
	{
		if (!stringCompareN(environ[i], name, name_len) && environ[i][name_len] == '=')
		{
			return (environ[i] + name_len + 1);
		}
	}
	return (NULL);
}

/**
 * locateExecutable - Locates the executable file associated with a given command.
 * @d: Data structure pointer
 * Return: void
 */
int locateExecutable(data *d)
{
	char *token, *path,
		*paths = malloc(strlen(getenvValue("PATH") ? getenvValue("PATH") : "") + 1);
	size_t token_len;
	int find = -1;

	if (!getenvValue("PATH"))
		goto step_out;
	stringCopy(paths, getenvValue("PATH"));
	if (paths == NULL)
		goto step_out;
	token = strtok(paths, ":");
	while (token)
	{
		token_len = strlen(token) + strlen(d->av[0]) + 2;
		path = malloc(token_len);
		if (path == NULL)
			return (find);
		stringCopy(path, token);
		stringConcatenate(path, "/");
		stringConcatenate(path, d->av[0]);
		if (access(path, F_OK) == 0)
		{
			free(d->av[0]);
			d->av[0] = strdup(path);
			free(path);
			find = 0;
			break;
		}
		free(path);
		token = strtok(NULL, ":");
	}
step_out:
	free(paths);
	return (find);
}

/**
 * createNewEntry - Initialize a new environment variable,
 *  or modify an existing one
 * @name: Variable name
 * @value: Variable value
 * Return: Pointer to the new entry
 */
char *createNewEntry(char *name, char *value)
{
	size_t new_len = strlen(name) + strlen(value) + 2;
	char *new_entry = malloc(new_len);

	if (new_entry == NULL)
		return (NULL);

	strcpy(new_entry, name);
	strcat(new_entry, "=");
	strcat(new_entry, value);

	return (new_entry);
}

/**
 * createNewEnviron - Initialize a new environment variable,
 *  or modify an existing one
 * @name: Variable name
 * @value: Variable value
 * Return: Pointer to the new environment
 */

 char **createNewEnviron(char *name, char *value)
{
	int env_len = 0, i = 0;
	char *new_entry;
	char **new_environ;

	while (environ[env_len])
		env_len++;
	new_entry = createNewEntry(name, value);
	if (new_entry == NULL)
		return (NULL);
	new_environ = getenvValue(name) ? malloc((env_len + 1) * sizeof(char *))
								: malloc((env_len + 2) * sizeof(char *));

	if (!new_environ)
	{
		free(new_entry);
		return (NULL);
	}
	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = malloc(strlen(environ[i]) + 1);
		if (!new_environ[i])
		{
			freeArray(new_environ);
			free(new_entry);
			return (NULL);
		}
		if (stringCompareN(environ[i], name, strlen(name)) == 0
		&& environ[i][strlen(name)] == '=')
			strcpy(new_environ[i], new_entry);
		else
			strcpy(new_environ[i], environ[i]);
	}
	if (!getenvValue(name))
	{
		new_environ[env_len] = new_entry;
		new_environ[env_len + 1] = NULL;
	}
	else
		new_environ[env_len] = NULL;
	return (new_environ);
}

/**
 * setEnv - Initialize a new environment variable or modify an existing one
 * @d: Data structure pointer
 * @name: Variable name
 * @value: Variable value
 * Return: 0 on success, -1 on failure
 */
int setEnv(data *d, char *name, char *value)
{
	char **new_environ;

	if (!name || !value)
		return (-1);

	new_environ = createNewEnviron(name, value);
	if (!new_environ)
		return (-1);
	environ = new_environ;
	d->flag_setenv = 1;

	return (0);
}
