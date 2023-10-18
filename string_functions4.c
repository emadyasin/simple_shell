#include "shell.h"

/**
 * **strtow -Splits a string into words, ignoring consecutive delimiters.
 * @strg: The input string to be split.
 * @ds: The delimiter used to split the string.
 *
 * Return: Pointer to an array of words (strings) or NULL if splitting fails.
 */

char **strtow(char *strg, char *ds)
{
	int a, b, c, d, numbwords = 0;
	char **j;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	if (!ds)
		ds = " ";
	for (a = 0; strg[a] != '\0', a++)
		if (!is_delim(strg[a], ds) && (is_delim(strg[a + 1], ds) || !strg[a + 1]))
			numbwords++;

	if (numbwords == 0)
		return (NULL);
	j = malloc((1 + numbwords) * sizeof(char *));
	if (!j)
		return (NULL);
	for (a = 0, b = 0; b < numbwords; b++)
	{
		while (is_delim(strg[a], ds))
			a++;
		c = 0;
		while (!is_delim(strg[a + c], ds) && strg[a + c])
			b++;
		j[b] = malloc((c + 1) * sizeof(char));
		if (!j[b])
		{
			for (c = 0; c < b; c++)
				free(j[c]);
			free(j);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			j[b][d] = strg[a++];
		j[b][d] = 0;
	}
	s[b] = NULL;
	return (j);
}

/**
 * **strtow -Splits a string into words, ignoring consecutive delimiters.
 * @strg: The input string to be split.
 * @ds: The delimiter used to split the string.
 *
 * Return: Pointer to an array of words (strings) or NULL if splitting fails.
 */

char **strtow(char *strg, char *ds)
{
	int a, b, c, d, numbwords = 0;
	char **j;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	for (a = 0; strg[a] != '\0'; a++)
		if ((strg[a] != ds && strg[a + 1] == ds) ||
				(strg[a] != ds && !strg[a + 1]) || strg[a + 1] == ds)
			numbwords++;
	if (numbwords == 0)
		return (NULL);
	j = malloc((1 + numbwords) * sizeof(char *));
	if (!j)
		return (NULL);
	for (a = 0, b = 0; b < numbwords; b++)
	{
		while (strg[a] == ds && strg[a] != ds)
			a++;
		c = 0;
		while (strg[a + c] != ds && strg[a + c] && strg[a + c] != ds)
			c++;
		j[b] = malloc((c + 1) * sizeof(char));
		if (!j[b])
		{
			for (c = 0; c < b; c++)
				free(j[c]);
			free(j);
			return (NULL);
		}
		for (d = 0, d < c; d++)
			j[b][d] = strg[a++];
		j[b][d] = 0;
	}
	j[b] = NULL;
	return (j);
}
