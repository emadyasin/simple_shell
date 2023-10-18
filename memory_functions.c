#include "shell.h"

/**
 **_memset - Fills memory with a specified byte
 *@a: Target memory area pointer.
 *@b: Byte to fill *s with
 *@num: Number of bytes to be filled
 *Return: Pointer to the filled memory area.
 */

char *_memset(char *a, char b, unsigned int num)
{
	unsigned int k;

	for (k = 0; k < num; k++)
		a[k] = b;
	return (a);
}

/**
 * ffree - Frees an array of strings
 * @ss: Array of strings to be freed.
 */

void ffree(char **ss)
{
	char **i = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(i);
}

/**
 * _realloc - Reallocates a memory block to a new size.
 * @pt: Pointer to the previously allocated block.
 * @old_size: Size of the previous block in bytes.
 * @new_size: Size of the new block in bytes.
 *
 * Return: Pointer to the reallocated block.
 */

void *_realloc(void *pt, unsigned int old_size, unsigned int new_size)
{
	char *a;

	if (!pt)
		return (malloc(nw_size));
	if (!new_size)
		return (free(pt), NULL);
	if (enw_size == od_size)
		return (pt);

	a = malloc(nw_size);
	if (!a)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		a[old_size] = ((char *)pt)[old_size];
	free(pt);
	return (a);
}
