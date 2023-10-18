#include "shell.h"

/**
 * _erratoi - Converts a string to an integer
 * @strg: Input string.
 * Return: Converted number, 0 if no numbers present, or -1 on error.
 */
int _erratoi(char *strg)
{
	int a = 0;
	unsigned long int res = 0;

	if (*strg == '+')
		strg++;
	for (a = 0;  strg[a] != '\0'; a++)
	{
		if (strg[a] >= '0' && strg[a] <= '9')
		{
			res *= 10;
			res += (strg[a] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - Outputs an error message
 * @cmdInfo: Parameter & return info struct
 * @estrg: Specified error message.
 * Return: Converted number if found, 0 otherwise, or -1 on error.
 */

void print_error(cmdInfo_t *cmdInfo, char *estrg)
{
	_eputs(cmdInfo->fname);
	_eputs(": ");
	print_d(cmdInfo->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(cmdInfo->argv[0]);
	_eputs(": ");
	_eputs(estrg);
}

/**
 * print_d - Prints an integer in base 10.
 * @inp: the integer to print.
 * @fid: File descriptor to write to
 *
 * Return: Number of characters printed
 */
int print_d(int inp, int fid)
{
	int (*__putchar)(char) = _putchar;
	int a, count = 0;
	unsigned int _abs_, current;

	if (fid == STDERR_FILENO)
		__putchar = _eputchar;
	if (inp < 0)
	{
		_abs_ = -inp;
		__putchar('-');
		count++;
	}
	else
		_abs_ = inp;
	current = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + current / a);
			count++;
		}
		current %= a;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @n: number to convert.
 * @ba: Base for conversion.
 * @af: Argument flags for conversion specifics
 *
 * Return: Convert string representation of the number.
 */

char *convert_number(long int n, int ba, int af)
{
	static char *array;
	static char buff[50];
	char sig = 0;
	char *pt;
	unsigned long i = n;

	if (!(af & CONVERT_UNSIGNED) && n < 0)
	{
		i = -n;
		sig = '-';

	}
	array = af & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buff[49];
	*pt = '\0';

	do	{
		*--pt = array[i % ba];
		i /= ba;
	} while (i != 0);

	if (sig)
		*--pt = sig;
	return (pt);
}

/**
 * remove_comments - Replaces first instance of '#' with '\0'
 * @buff: String to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buff)
{
	int a;

	for (a = 0; buff[a] != '\0'; a++)
		if (buff[a] == '#' && (!a || buff[a - 1] == ' '))
		{
			buff[a] = '\0';
			break;
		}
}
