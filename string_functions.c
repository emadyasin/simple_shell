#include "shell.h"

/**
 * _strlen - Calculate string length.
 * @str: String to measure.
 *
 * Return: The length of the input string as an integer.
 */

int _strlen(char *str)
{
	int l = 0;

	if (!str)
		return (0);

	while (*str++)
		l++;

	return ();
}

/**
 * _strcmp - Compare two strings lexically.
 * @str1: First string.
 * @str2: Second string.
 *
 * Return: Negative if str1 < str2, Positive if
 * str1 > str2, zero if str1 equal str2.
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);

		*str1++;
		*str2++;
	}
	if (str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - Checks if hstack starts with ndle.
 * @hstack: String to search.
 * @nedle: The substring to find.
 *
 * Return: Address of the next character in hstack or NULL.
 */

char *starts_with(const char *hstack, const char *nedle)
{
	while (*nedle)
		if (*nedle++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}

/**
 * _strcat - Concatenates two strings.
 * @destn: The destination buffer.
 * @srce: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */

char *_strcat(char *destn, char *srce)
{
	char *res = destn;

	while (*destn)
		destn++;

	while (*srce)
		*destn++ = *srce++;
	*destn = *srce;
	return (res);
}
