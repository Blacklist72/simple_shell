#include "main.h"

/**
 * execute - executes a command
 * @tokens: array of tokens
 * @argv: array of arguments
 * @env: array of environment variables
 * Return: 0 on success, 1 on failure
 */
int execute(char **tokens, char **argv, char **env)
{
    char *command = get_path(tokens[0]);
    pid_t child_pid;
    int status = 0;

    if (checkBuiltins(tokens, argv, env) == 0)
        return 0;

    if (command == NULL)
        return 1;

    if (access(command, X_OK) == 0)
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            perror(argv[0]);
            free(command);
            return 1;
        }
        else if (child_pid == 0)
        {
            if (execve(command, tokens, env) == -1)
            {
                perror(argv[0]);
                free(command);
                exit(1);
            }
        }
        else
        {
            wait(&status);
        }
    }
    else
    {
        free(command);
        return 1;
    }

    free(command);
    return status;
}

