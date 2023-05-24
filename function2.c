#include "main.h"


/**
 * copyString - copies a string
 * @dest: destination string
 * @src: source string
 * Return: pointer to the copied string
 */
char *copyString(char *dest, const char *src)
{
    int i = 0;

    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';

    return dest;
}


/**
 * concatenateStrings - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: pointer to the concatenated string
 */
char *concatenateStrings(char *dest, const char *src)
{
    int i = 0;
    int j = 0;

    while (dest[i] != '\0')
        i++;

    while (src[j] != '\0')
    {
        dest[i] = src[j];
        j++;
        i++;
    }

    dest[i] = '\0';

    return dest;
}


/**
 * freeDoublePointer - frees a double pointer
 * @ptr: double pointer to be freed
 * Return: void
 */

void freeDoublePointer(char **ptr)
{
	int i = 0;

	if (ptr == NULL)
		return;

	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}

	free(ptr);
}

/**
 * freePointer - frees a pointer
 * @ptr: pointer to be freed
 * Return: void
 */
void freePointer(char *ptr)
{
    if (ptr != NULL)
    {
        free(ptr);
        ptr = NULL;
    }
}
