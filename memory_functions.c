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
 * @od_size: Size of the previous block in bytes.
 * @nw_size: Size of the new block in bytes.
 *
 * Return: Pointer to the reallocated block.
 */

void *_realloc(void *pt, unsigned int od_size, unsigned int nw_size)
{
	char *a;

	if (!pt)
		return (malloc(nw_size));
	if (!nw_size)
		return (free(pt), NULL);
	if (nw_size == od_size)
		return (pt);

	a = malloc(nw_size);
	if (!a)
		return (NULL);

	od_size = od_size < nw_size ? od_size : nw_size;
	while (od_size--)
		a[od_size] = ((char *)pt)[od_size];
	free(pt);
	return (a);
}
