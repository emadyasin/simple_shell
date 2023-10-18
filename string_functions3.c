#include "shell.h"

/**
 * _strcpy - Copies up to 'i' characters from the source
 * string to the destination buffer.
 * @destn: Buffer to copy into.
 * @srce: Srting to copy from.
 * @i: Matimum number of characters to copy.
 *
 * Return: Pointer to the destination buffer.
 */

char *_strcpy(char *destn, char *srce, int i)
{
	int a, b;
	char *d = destn;

	a = 0;
	while (srce[a] != '\0' && a < i - 1)
	{
		destn[a] = srce[a];
		a++;
	}
	if (a < i)
	{
		b = a;
		while (b < i)
		{
			destn[b] = '\0';
			b++;
		}
	}
	return (d);
}

/**
 * *_strncat - Concatenates up to 'i' btes from the source string
 * onto the the end of the destination string.
 * @destn: The target string where characters will be appended.
 * @srce: The source string from which characters are taken.
 * @i: Maximum nuber of bytes to append from 'srce'.
 *
 * Return: Pointer to the concatenated string (destn).
 */

char *_strncat(char *destn, char *srce, int i)
{
	int a, b;
	char *d = destn;

	a = 0;
	b = 0;
	while (destn[a] != '\0')
		a++;
	while (srce[a] != '\0' && b < i)
	{
		destn[a] = srce[b];
		a++;
		b++;
	}
	if (b < i)
		destn[a] = '\0';
	return (d);
}

/**
 * *_strchr - Locates the first occurrence of a character in a string.
 * @strg: The string to be searched.
 * @c: The character to look for.
 *
 * Return: Pointer to the first occurrence of the character in the string,
 * or NULL if the character is not found.
 */

char *_strchr(char *strg, char c)
{
	do {
		if (*strg == c)
			return (strg);
	} while (*strg++ != '\0');

	return (NULL);
}
