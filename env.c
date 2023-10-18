#include "shell.h"

/**
 * _myenv - Displays the current environment.
 * @cmdInfo: command structure
 * Return: Always 0
 */

int _myenv(cmdInfo_t *cmdInfo)
{
	print_list_str(cmdInfo->env);
	return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable.
 * @cmdInfo: Command structure.
 * @nam: environemt variable name
 * nde: Node
 *
 * Return: Value of the variables.
 */
char *_getenv(cmdInfo_t *cmdInfo, const char *nam)
{
	list_t *nde = cmdInfo->env;
	char *a;

	while (nde)
	{
		a = starts_with(nde->str, nam);
		if (a && *a)
			return (a);
		nde = nde->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Creates or updates an evironment variable.
 * @cmdInfo: command structure.
 *  Return: Always 0
 */

int _mysetenv(cmdInfo_t *cmdInfo)
{
	if (cmdInfo->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(cmdInfo, cmdInfo->argv[1], cmdInfo->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Deletes an environment variable
 * @cmdInfo: comman Structure
 *  Return: Always 0
 */
int _myunsetenv(cmdInfo_t *cmdInfo)
{
	int K;

	if (cmdInfo->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= cmdInfo->argc; k++)
		_unsetenv(cmdInfo, cmdInfo->argv[k]);

	return (0);
}

/**
 * populate_env_list - fills the environment linked list
 * @cmdInfo: Command Structure.
 * Return: Always 0
 */
int populate_env_list(cmdInfo_t *cmdInfo)
{
	list_t *nde = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		add_node_end(&nde, environ[k], 0);
	cmdInfo->env = nde;
	return (0);
}
