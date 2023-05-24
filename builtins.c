#include "main.h"

/**
 * displayEnvironment - prints the environment variables
 * @env: array of environment variables
 */
void displayEnvironment(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
    {
        for (int j = 0; env[i][j] != '\0'; j++)
        {
            write(STDOUT_FILENO, &env[i][j], 1);
        }
        write(STDOUT_FILENO, "\n", 1);
    }
}


/**
 * checkBuiltins - checks if a command is a builtin
 * @tokens: array of tokens
 * @argv: array of arguments
 * @env: array of environment variables
 * Return: 0 if builtin, 1 if not
 */
int checkBuiltins(char **tokens, char **argv, char **env)
{
    if (strncmp(tokens[0], "exit", 4) == 0)
    {
        freeDoublePointer(tokens);
        exit(EXIT_SUCCESS);
    }
    if (strncmp(tokens[0], "env", 3) == 0)
    {
        displayEnvironment(env);
        return 0;
    }
    return 1;
}
