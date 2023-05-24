#include "main.h"

/**
 * getEnvironmentVariable - gets an environment variable
 * @name: name of the environment variable
 * Return: pointer to the environment variable
 */
char *getEnvironmentVariable(char *name)
{
    char **env = NULL;
    char *var = NULL;
    char *value = NULL;
    int i = 0;
    int j = 0;
    int len = 0;

    env = environ;
    while (env[i] != NULL)
    {
        var = env[i];
        len = strlen(name);
        for (j = 0; j < len; j++)
        {
            if (name[j] != var[j])
                break;
        }
        if (j == len && var[j] == '=')
        {
            value = var + len + 1;
            break;
        }
        i++;
    }
    return value;
}

