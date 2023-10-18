#include "shell.h"

/**
 * get_environ - Retrieves a copy of the environment string array.
 * @cmdInfo: Command Structure
 * Return: Always 0
 */
char **get_environ(cmdInfo_t *cmdInfo)
{
	if (!cmdInfo->environ || cmdInfo->env_changed)
	{
		cmdInfo->environ = list_to_strings(cmdInfo->env);
		cmdInfo->env_changed = 0;
	}

	return (cmdInfo->environ);
}

/**
 * _unsetenv - Deletes an environment variable
 * @cmdInfo: Command structure.
 * @vars: Evironment variables property.
 *  Return: 1 if deleted, 0 otherwise
 *  nde: node
 */
int _unsetenv(cmdInfo_t *cmdInfo, char *vars)
{
	list_t *nde = cmdInfo->env;
	size_t k = 0;
	char *a;

	if (!nde || !vars)
		return (0);

	while (nde)
	{
		a = starts_with(nde->str, vars);
		if (a && *a == '=')
		{
			cmdInfo->env_changed = delete_node_at_index(&(cmdInfo->env), K);
			K = 0;
			nde = cmdInfo->env;
			continue;
		}
		nde = nde->next;
		k++;
	}
	return (cmdInfo->env_changed);
}

/**
 * _setenv - Creates or updates an environement variable.
 * @cmdInfo: Command Structure
 * @vars: Environement variable property
 * @val: Value for the environment variable.
 *  Return: Always 0
 */
int _setenv(cmdInfo_t *cmdInfo, char *vars, char *val)
{
	char *buff = NULL;
	list_t *nde;
	char *a;

	if (!vars || !val)
		return (0);

	buff = malloc(_strlen(vars) + _strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, vars);
	_strcat(buff, "=");
	_strcat(buff, val);
	nde = cmdInfo->env;
	while (nde)
	{
		a = starts_with(nde->str, vars);
		if (a && *a == '=')
		{
			free(nde->str);
			nde->str = buff;
			cmdInfo->env_changed = 1;
			return (0);
		}
		nde = nde->next;
	}
	add_node_end(&(cmdInfo->env), buff, 0);
	free(buff);
	cmdInfo->env_changed = 1;
	return (0);
}
