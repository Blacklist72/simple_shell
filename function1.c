#include "main.h"

/**
 * getStringLength - returns the length of a string
 * @str: string to be measured
 * Return: length of string
 */
int getStringLength(char *str)
{
    int length = 0;

    while (str[length] != '\0')
        length++;
    
    return length;
}


/**
 * compareStrings - compares two strings
 * @str1: first string
 * @str2: second string
 * @n: number of bytes to compare
 * Return: 0 if strings are equal, -1 if not
 */
int compareStrings(char *str1, char *str2, int n)
{
    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0' && i < n)
    {
        if (str1[i] != str2[i])
            return -1;
        i++;
    }

    if (i == n)
        return 0;
    return -1;
}


/**
 * duplicateString - duplicates a string
 * @str: string to be duplicated
 * Return: pointer to the duplicated string
 */
char *duplicateString(char *str)
{
    int i = 0;
    char *dup = NULL;

    if (str == NULL)
        return NULL;

    int length = getStringLength(str);
    dup = malloc(sizeof(char) * (length + 1));
    if (dup == NULL)
        return NULL;

    while (str[i] != '\0')
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';

    return dup;
}


/**
 * handleSIGINT - handles the SIGINT signal
 * @signalNumber: signal number
 * Return: void
 */
void handleSIGINT(int signalNumber)
{
    (void)signalNumber;
    signal(SIGINT, handleSIGINT);
    fflush(stdout);
}

