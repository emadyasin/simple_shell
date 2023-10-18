#include "shell.h"

/**
 * bfree - Frees a pointer and sets its value to NULL.
 * @pt: Address of the pointer to be freed.
 *
 * Return: 1 if successfully freed, otherwise 0.
 */

int bfree(void **pt)
{
	if (pt && *pt)
	{
		free(*pt);
		*pt = NULL;
		return (1);
	}
	return (0);
}
