#include "main.h"

/**
 * stringDuplicate - Returns a pointer to a newly allocated space in memory,
 *                   which contains a copy of the string given as a parameter.
 *
 * @str: Input string
 *
 * Return: Pointer to the duplicated string
 */
char *stringDuplicate(const char *str)
{
	int i, len = 0;
	char *result;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	result = (char *)malloc((len + 1) * sizeof(char));

	if (result == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		result[i] = str[i];

	return (result);
}

/**
 * isNumber - Checks if a string is a number
 * @status: String to be checked
 * Return: 1 if the string is a number, 0 otherwise
 */
int isNumber(const char *status)
{
	if (status == NULL || status[0] == '\0')
		return (0);
	while (*status)
	{
		if (!isDigit(*status))
			return (0);
		status++;
	}
	return (1);
}

/**
 * isDigit - Checks if a character is a digit
 * @c: Character
 * Return: 1 if the character is a digit, 0 otherwise
 */
int isDigit(int c)
{
	return (c >= '0' && c <= '9');
}
