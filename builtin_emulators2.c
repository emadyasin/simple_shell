#include "shell.h"

/**
 * _myhistory - Lists command history with line numbers.
 * @info: Command structure.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Assigns alias to a string.
 * @info: parameter structure
 * @str: Alias string.
 *
 * Return: 0 on success, 1 on error
 */

int unset_alias(info_t *info, char *str)
{
	char *a, b;
	int res;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	res = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*a = b;
	return (res);
}

/**
 * set_alias - Assigns an alias to a string.
 * @info: parameter structure
 * @strg: Alias string.
 *
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *a;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Dispalys the alias string
 * @node: Alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *a = NULL, *c = NULL;

	if (node)
	{
		a = _strchr(node->str, '=');
		for (c = node->str; c <= a; c++)
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
 * @nfo: Command structure.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *a = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		a = _strchr(info->argv[j], '=');
		if (a)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
