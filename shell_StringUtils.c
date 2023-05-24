#include "main.h"

/**
 * stringLength - Returns the number of characters in a string
 * @str: Input string
 * Return: Number of characters in the string
 */
unsigned int stringLength(char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
		;
	return (i);
}

/**
 * stringCompare - Compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: An integer indicating the result of the comparison
 */
int stringCompare(const char *s1, const char *s2)
{
	int i;
	int result = 0;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
		{
			result = s1[i] - s2[i];
			break;
		}
	}

	return (result);
}

/**
 * stringCompareN - Compares two strings up to a certain length
 * @s1: First string
 * @s2: Second string
 * @n: Maximum number of characters to compare
 * Return: An integer indicating the result of the comparison
 */
int stringCompareN(const char *s1, const char *s2, int n)
{
	int i;
	int result = 0;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (i >= n)
			break;
		if (s1[i] != s2[i])
		{
			result = s1[i] - s2[i];
			break;
		}
	}

	return (result);
}

/**
 * stringCopy - Copies a string
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to the destination string
 */
char *stringCopy(char *dest, const char *src)
{
	int len;

	for (len = 0; src[len] != '\0'; ++len)
	{
		dest[len] = src[len];
	}
	dest[len] = '\0';
	return (dest);
}

/**
 * stringConcatenate - Concatenates two strings
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to the destination string
 */
char *stringConcatenate(char *dest, const char *src)
{
	char *result = dest;

	while (*dest != '\0')
		dest++;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return (result);
}
