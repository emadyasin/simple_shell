#include "shell.h"

/**
 * _strcpy - Copies the source string into the destination buffer.
 * @destn: Destination buffer.
 * @srce: Source string.
 *
 * Return: Pointer to the destination buffer.
 */

char *_strcpy(char *destn, char *srce)
{
	int a = 0;

	if (destn == srce || srce == 0)
		return (destn);
	while (srce[a])
	{
		destn[a] = srce[a];
		a++;
	}
	destn[a] = 0;
	return (destn);
}

/**
 * _strdup - Creates a copy of the given string.
 * @strg: String to be duplication.
 *
 * Return: Pointer to the newly duplicated string.
 */

char *_strdup(const char *strg)
{
	int len = 0;
	char *res;

	if (strg == NULL)
		return (NULL);
	while (*strg++)
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	for (len++; len--)
		res[len] = *--strg;
	return (res);
}

/**
 * _puts - Displays a given string.
 * @strg: String to print.
 *
 * Return: None.
 */

void _puts(char *strg)
{
	int a = 0;

	if (!strg)
		return;
	while (strg[a] != '\0')
	{
		_putchar(strg[a]);
		a++;
	}
}

/**
 * _putchar - Outputs the character 'c' to standard output.
 * @c: Character to output.
 *
 * Return: 1 on success, -1 on error with errno set.
 */

int _putchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}
