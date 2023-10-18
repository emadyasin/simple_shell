#include "shell.h"

/**
 *_eputs - Prints a given string
 * @strg: String to printe.
 *
 * Return: None
 */
void _eputs(char *strg)
{
	int k = 0;

	if (!strg)
		return;
	while (strg[k] != '\0')
	{
		_eputchar(strg[k]);
		k++;
	}
}

/**
 * _eputchar - Outputs a character c to stderr
 * @p: Character to print
 *
 * Return: 1 on success, -1 on error with errno set.
 */

int _eputchar(char p)
{
	static int k;
	static char buff[WRITE_BUFF_SIZE];

	if (p == BUFF_FLUSH || k >= WRITE_BUFF_SIZE)
	{
		write(2, buff, k);
		k = 0;
	}
	if (p != BUFF_FLUSH)
		buff[k++] = p;
	return (1);
}

/**
 * _putfd - Outputs a string to a specified fid
 * @p: Character to print
 * @fid: File descriptor to write to.
 *
 * Return: 1 on success, -1 on error with errno set.
 */

int _putfd(char p, int fid)
{
	static int k;
	static char buff[WRITE_BUFF_SIZE];

	if (p == BUFF_FLUSH || k >= WRITE_BUFF_SIZE)
	{
		write(fid, buff, k);
		k = 0;
	}
	if (p != BUFF_FLUSH)
		buff[k++] = p;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @strg: the string to be printed
 * @fid: File descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int _putsfd(char *strg, int fid)
{
	int k = 0;

	if (!strg)
		return (0);
	while (*strg)
	{
		k += _putfd(*strg++, fid);
	}
	return (k);
}
