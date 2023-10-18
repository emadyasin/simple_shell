#include "shell.h"

/**
 * _myhistory - Lists command history with line numbers.
 * @cmdInfo: Command structure.
 *  Return: Always 0
 */
int _myhistory(cmdInfo_t *cmdInfo)
{
	print_list(cmdInfo->history);
	return (0);
}

/**
 * unset_alias - Assigns alias to a string.
 * @cmdInfo: parameter structure
 * @strg: Alias string.
 *
 * Return: 0 on success, 1 on error
 */

int unset_alias(cmdInfo_t *cmdInfo, char *strg)
{
	char *a, b;
	int res;

	a = _strchr(strg, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	res = delete_node_at_index(&(cmdInfo->alias),
		get_node_index(cmdInfo->alias, node_starts_with(cmdInfo->alias, strg, -1)));
	*a = b;
	return (res);
}

/**
 * set_alias - Assigns an alias to a string.
 * @cmdInfo: parameter structure
 * @strg: Alias string.
 *
 * Return: 0 on success, 1 on error.
 */
int set_alias(cmdInfo_t *cmdInfo, char *strg)
{
	char *a;

	a = _strchr(strg, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (unset_alias(cmdInfo, strg));

	unset_alias(cmdInfo, strg);
	return (add_node_end(&(cmdInfo->alias), strg, 0) == NULL);
}

/**
 * print_alias - Dispalys the alias string
 * @nde: Alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *nde)
{
	char *a = NULL, *c = NULL;

	if (nde)
	{
		a = _strchr(nde->strg, '=');
		for (c = nde->str; c <= a; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(a + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Simulates the 'alias' builtin command.
 * @cmdInfo: Command structure.
 *  Return: Always 0
 */
int _myalias(cmdInfo_t *cmdInfo)
{
	int j = 0;
	char *a = NULL;
	list_t *nde = NULL;

	if (cmdInfo->argc == 1)
	{
		nde = cmdInfo->alias;
		while (nde)
		{
			print_alias(nde);
			nde = nde->next;
		}
		return (0);
	}
	for (j = 1; cmdInfo->argv[j]; j++)
	{
		a = _strchr(cmdInfo->argv[j], '=');
		if (a)
			set_alias(cmdInfo, cmdInfo->argv[j]);
		else
			print_alias(nde_starts_with(cmdInfo->alias, cmdInfo->argv[j], '='));
	}

	return (0);
}
