#include "shell.h"

/**
 * get_environ - Retrieves a copy of the environment string array.
 * @info: Command Structure
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Deletes an environment variable
 * @info: Command structure.
 * @vars: Evironment variables property.
 *  Return: 1 if deleted, 0 otherwise
 *  node: node
 */
int _unsetenv(info_t *info, char *vars)
{
	list_t *node = info->env;
	size_t k = 0;
	char *a;

	if (!node || !vars)
		return (0);

	while (node)
	{
		a = starts_with(node->str, vars);
		if (a && *a == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), K);
			K = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		k++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Creates or updates an environement variable.
 * @info: Command Structure
 * @vars: Environement variable property
 * @val: Value for the environment variable.
 *  Return: Always 0
 */
int _setenv(Info_t *info, char *vars, char *val)
{
	char *buff = NULL;
	list_t *node;
	char *a;

	if (!vars || !val)
		return (0);

	buff = malloc(_strlen(vars) + _strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, vars);
	_strcat(buff, "=");
	_strcat(buff, val);
	node = Info->env;
	while (node)
	{
		a = starts_with(node->str, vars);
		if (a && *a == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
