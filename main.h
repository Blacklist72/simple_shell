#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;  // Declaration of the extern variable environ

// Function prototypes

/**
 * tokenize - Tokenizes a string based on whitespace
 * @line: The string to be tokenized
 * Return: An array of tokens
 */
char **tokenize(char *line);

/**
 * getStringLength - Calculates the length of a string
 * @str: The input string
 * Return: The length of the string
 */
int getStringLength(char *str);

/**
 * compareStrings - Compares two strings up to a specified number of characters
 * @str1: The first string
 * @str2: The second string
 * @n: The number of characters to compare
 * Return: 0 if strings are equal, -1 if not
 */
int compareStrings(char *str1, char *str2, int n);

/**
 * duplicateString - Creates a duplicate of a string
 * @str: The input string
 * Return: The duplicated string
 */
char *duplicateString(char *str);

/**
 * handleSIGINT - Handles the SIGINT signal
 * @sig_num: The signal number
 * Return: void
 */
void handleSIGINT(int sig_num);

/**
 * concatenateStrings - Concatenates two strings
 * @dest: The destination string
 * @src: The source string
 * Return: The concatenated string
 */
char *concatenateStrings(char *dest, char *src);

/**
 * copyString - Copies a string
 * @dest: The destination string
 * @src: The source string
 * Return: The copied string
 */
char *copyString(char *dest, char *src);

/**
 * getEnvironmentVariable - Gets the value of an environment variable
 * @name: The name of the environment variable
 * Return: The value of the environment variable
 */
char *getEnvironmentVariable(char *name);

/**
 * make_path - Combines a directory path and a command
 * @path: The directory path
 * @cmd: The command
 * Return: The combined path
 */
char *make_path(char *path, char *cmd);

/**
 * get_path - Searches for the executable path of a command
 * @cmd: The command
 * Return: The executable path of the command
 */
char *get_path(char *cmd);

/**
 * execute - Executes a command with the given arguments
 * @tokens: The command and its arguments as an array of tokens
 * @argv: The array of arguments
 * @env: The array of environment variables
 * Return: The exit status of the executed command
 */
int execute(char **tokens, char **argv, char **env);

/**
 * freeDoublePointer - Frees a double pointer
 * @ptr: The double pointer to be freed
 * Return: void
 */
void freeDoublePointer(char **ptr);

/**
 * freePointer - Frees a pointer
 * @ptr: The pointer to be freed
 * Return: void
 */
void freePointer(char *ptr);

/**
 * @tokens: The command and its arguments as an array of tokens
 * @argv: The array of arguments
 * @env: The array of environment variables
 * Return: 0 if the command is a builtin, 1 if not
 */
int checkBuiltins(char **tokens, char **argv, char **env);

#endif /* _MAIN_H_ */
