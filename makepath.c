#include "main.h"

/**
 * make_path - creates a path to a command
 * @path: path to the directory
 * @cmd: command name
 * Return: pointer to the constructed path
 */
char *make_path(char *path, char *cmd)
{
    int path_len = getStringLength(path);
    int cmd_len = getStringLength(cmd);
    int total_len = path_len + cmd_len + 2; // +1 for '/' and +1 for null terminator

    char *cmd_path = malloc(sizeof(char) * total_len);
    if (cmd_path == NULL)
        return NULL;

    copyString(cmd_path, path);
    concatenateStrings(cmd_path, "/");
    concatenateStrings(cmd_path, cmd);

    return cmd_path;
}


/**
 * get_path - gets the path of a command
 * @cmd: command to get the path of
 * Return: path of the command
 */
char *get_path(char *cmd)
{
    char *path = getEnvironmentVariable("PATH");
    char *path_copy = duplicateString(path);
    char *token = strtok(path_copy, ":");
    char *cmd_path = NULL;
    struct stat st;

    if (cmd == NULL)
    {
        free(path_copy);
        return NULL;
    }

    // Check if the command is already an absolute path
    if (stat(cmd, &st) == 0)
    {
        free(path_copy);
        return duplicateString(cmd);
    }

    // Iterate through each path in the environment variable "PATH"
    while (token != NULL)
    {
        cmd_path = make_path(token, cmd);
        if (stat(cmd_path, &st) == 0)
        {
            free(path_copy);
            return cmd_path;
        }
        free(cmd_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
