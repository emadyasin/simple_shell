#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @hed: address of pointer to head node
 * @strg: str field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **hed, const char *strg, int n)
{
	list_t *new_hed;

	if (!hed)
		return (NULL);
	new_hed = malloc(sizeof(list_t));
	if (!new_hed)
		return (NULL);
	_memset((void *)new_hed, 0, sizeof(list_t));
	new_hed->n = n;
	if (strg)
	{
		new_hed->strg = _strdup(strg);
		if (!new_hed->strg)
		{
			free(new_hed);
			return (NULL);
		}
	}
	new_hed->next = *hed;
	*hed = new_hed;
	return (new_hed);
}

/**
 * add_node_end - adds a node to the end of the list
 * @hed: address of pointer to head node
 * @strg: str field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **hed, const char *strg, int n)
{
	list_t *new_nod, *nod;

	if (!hed)
		return (NULL);

	nod = *hed;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	_memset((void *)new_nod, 0, sizeof(list_t));
	new_nod->n = n;
	if (strg)
	{
		new_nod->strg = _strdup(strg);
		if (!new_nod->strg)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = new_nod;
	}
	else
		*hed = new_nod;
	return (new_nod);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @m: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *m)
{
	size_t k = 0;

	while (m)
	{
		_puts(m->strg ? m->strg : "(nil)");
		_puts("\n");
		m = m->next;
		k++;
	}
	return (k);
}

/**
 * delete_node_at_index - deletes node at given index
 * @hed: address of pointer to first node
 * @indx: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **hed, unsigned int indx)
{
	list_t *nod, *prev_nod;
	unsigned int k = 0;

	if (!hed || !*hed)
		return (0);

	if (!indx)
	{
		nod = *hed;
		*hed = (*hed)->next;
		free(nod->strg);
		free(nod);
		return (1);
	}
	nod = *hed;
	while (nod)
	{
		if (k == indx)
		{
			prev_nod->next = nod->next;
			free(nod->strg);
			free(nod);
			return (1);
		}
		k++;
		prev_nod = nod;
		nod = nod->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_pt: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_pt)
{
	list_t *nod, *next_nod, *head;

	if (!head_pt || !*head_pt)
		return;
	head = *head_pt;
	nod = head;
	while (nod)
	{
		next_nod = nod->next;
		free(nod->strg);
		free(nod);
		nod = next_nod;
	}
	*head_pt = NULL;
}
