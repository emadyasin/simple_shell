#include "shell.h"

/**
 * interactive - Checks if the shell is in interactive mode.
 * @cmdInfo: Address of the structure.
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(cmdInfo_t *cmdInfo)
{
	return (isatty(STDIN_FILENO) && cmdInfo->readfd <= 2);
}

/**
 * is_delim - Determines if a character is within a delimiter string.
 * @a: Character to evaluate.
 * @delims: Delimeter string
 * Return: 1 if character is a delimiter, 0 if false
 */

int is_delim(char a, char *delims)
{
	while (*delims)
		if (*delims++ == a)
			return (1);
	return (0);
}

/**
 *_isalpha - Determines if a character is alphabetic.
 *@i: Character to input
 *Return: 1 if  alphabetic, 0 otherwise
 */

int _isalpha(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - Converts a string to an integer.
 *@z:Input string.
 *Return: The converted number or 0 if no number present.
 */

int _atoi(char *z)
{
	int a, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (a = 0;  z[a] != '\0' && flag != 2; a++)
	{
		if (z[a] == '-')
			sign *= -1;

		if (z[a] >= '0' && z[a] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (z[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}
