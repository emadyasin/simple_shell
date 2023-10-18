#include "shell.h"

/**
 *_eputs - Prints a given string
 * @str: String to printe.
 *
 * Return: None
 */
void _eputs(char *str)
{
	int k = 0;

	if (!str)
		return;
	while (str[k] != '\0')
	{
		_eputchar(str[k]);
		k++;
	}
}

/**
 * _eputchar - Outputs a character to stderr
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
 * @fd: File descriptor to write to.
 *
 * Return: 1 on success, -1 on error with errno set.
 */

int _putfd(char p, int fd)
{
	static int k;
	static char buff[WRITE_BUFF_SIZE];

	if (p == BUFF_FLUSH || k >= WRITE_BUFF_SIZE)
	{
		write(fd, buff, k);
		k = 0;
	}
	if (p != BUFF_FLUSH)
		buff[k++] = p;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: File descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int _putsfd(char *str, int fd)
{
	int k = 0;

	if (!str)
		return (0);
	while (*str)
	{
		k += _putfd(*str++, fd);
	}
	return (k);
}
