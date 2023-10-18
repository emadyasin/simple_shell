#include "shell.h"

/**
 * list_len - determines length of linked list
 * @m: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *m)
{
	size_t k = 0;

	while (m)
	{
		m = m->next;
		k++;
	}
	return (k);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @hed: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *hed)
{
	list_t *nod = hed;
	size_t k = list_len(hed), r;
	char **strgs;
	char *strg;

	if (!hed || !k)
		return (NULL);
	strgs = malloc(sizeof(char *) * (k + 1));
	if (!strgs)
		return (NULL);
	for (k = 0; nod; nod = nod->next, k++)
	{
		strg = malloc(_strlen(nod->strg) + 1);
		if (!strg)
		{
			for (r = 0; r < k; r++)
				free(strgs[r]);
			free(strgs);
			return (NULL);
		}

		strg = _strcpy(strg, nod->strg);
		strgs[k] = strg;
	}
	strs[k] = NULL;
	return (strgs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @m: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *m)
{
	size_t k = 0;

	while (m)
	{
		_puts(convert_number(m->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(m->strg ? m->strg : "(nil)");
		_puts("\n");
		m = m->next;
		k++;
	}
	return (k);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @nod: pointer to list head
 * @prefx: string to match
 * @d: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *nod, char *prefx, char d)
{
	char *a = NULL;

	while (nod)
	{
		a = starts_with(nod->strg, prefx);
		if (a && ((d == -1) || (*a == d)))
			return (nod);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @hed: pointer to list head
 * @nod: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *hed, list_t *nod)
{
	size_t k = 0;

	while (hed)
	{
		if (hed == nod)
			return (k);
		hed = hed->next;
		k++;
	}
	return (-1);
}
