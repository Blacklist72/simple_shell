#include "main.h"

/**
 * tokenize - tokenizes a string
 * @line: string to tokenize
 * Return: pointer to an array of tokens
 */
char **tokenize(char *line)
{
    char **tokens = NULL;  // Array to store tokens
    char *token = NULL;    // Current token
    int i = 0, len = 0;    // Index and length variables

    len = getStringLength(line);
    if (len == 0)
        return NULL;

    tokens = malloc(sizeof(char *) * (len + 1));  // Allocate memory for tokens array
    if (tokens == NULL)
    {
        perror("Fatal Error");
        return NULL;
    }

    token = strtok(line, " \n\t\r");  // Tokenize the line using delimiters

    while (token != NULL)
    {
        tokens[i] = token;       // Store token in the tokens array
        token = strtok(NULL, " \n\t\r");  // Get the next token
        i++;
    }

    tokens[i] = NULL;  // Set the last element of the tokens array to NULL

    return tokens;  // Return the array of tokens
}
