#include "shell.h"

/**
 * _myenv - Displays the current environment.
 * @info: command structure
 * Return: Always 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable.
 * @info: Command structure.
 * @name: environemt variable name
 * node: Node
 *
 * Return: Value of the variables.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *a;

	while (node)
	{
		a = starts_with(node->str, name);
		if (a && *a)
			return (a);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Creates or updates an evironment variable.
 * @info: command structure.
 *  Return: Always 0
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Deletes an environment variable
 * @info: comman Structure
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int K;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= info->argc; k++)
		_unsetenv(info, info->argv[k]);

	return (0);
}

/**
 * populate_env_list - fills the environment linked list
 * @info: Command Structure.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		add_node_end(&node, environ[k], 0);
	info->env = node;
	return (0);
}
