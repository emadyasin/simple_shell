#include "shell.h"

/**
 * is_chain - Checks if the current character is a chain delimeter
 * @cmdInfo: command structure
 * @buff: Characture buffer
 * @a: Current position in buffer.
 *
 * Return: 1 if delimeter, 0 otherwise.
 */
int is_chain(cmdInfo_t *cmdInfo, char *buff, size_t *a)
{
	size_t k = *a;

	if (buff[k] == '|' && buff[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		cmdInfo->cmd_buf_type = CMD_OR;
	}
	else if (buff[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		cmdInfo->cmd_buf_type = CMD_AND;
	}
	else if (buff[k] == ';') /* found end of this command */
	{
		buff[k] = 0; /* replace semicolon with null */
		cmdInfo->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*a = k;
	return (1);
}

/**
 * check_chain - Evaluates chaining continuation based on previous status.
 * @cmdInfo: Command structure.
 * @buff: Character buffer
 * @a: Current position in buffer.
 * @b: Starting position in buffer.
 * @leng: Buffer length.
 *
 * Return: Void
 */

void check_chain(cmdInfo_t *cmdInfo, char *buff,
		size_t *a, size_t b, size_t leng)
{
	size_t k = *a;

	if (cmdInfo->cmd_buf_type == CMD_AND)
	{
		if (cmdInfo->status)
		{
			buff[b] = 0;
			k = leng;
		}
	}
	if (cmdInfo->cmd_buf_type == CMD_OR)
	{
		if (!cmdInfo->status)
		{
			buf[b] = 0;
			k = leng;
		}
	}

	*a = k;
}

/**
 * replace_alias - substitutes aliases in the tokenized string
 * @cmdInfo: Command structure.
 *
 * Return: 1 if substituted, 0 otherwise.
 */

int replace_alias(cmdInfo_t *cmdInfo)
{
	int b;
	list_t *nde;
	char *a;

	for (b = 0; b < 10; b++)
	{
		nde = nde_starts_with(info->alias, cmdInfo->argv[0], '=');
		if (!nde)
			return (0);
		free(cmdInfo->argv[0]);
		a = _strchr(nde->strg, '=');
		if (!a)
			return (0);
		a = _strdup(a + 1);
		if (!a)
			return (0);
		cmdInfo->argv[0] = a;
	}
	return (1);
}

/**
 * replace_vars - Substitutes variables in the tokenized string
 * @cmdInfo: Command structure.
 *
 * Return: 1 if substituted, 0 otherwise
 */

int replace_vars(cmdInfo_t *cmdInfo)
{
	int b = 0;
	list_t *nde;

	for (b = 0; cmdInfo->argv[b]; b++)
	{
		if (cmdInfo->argv[b][0] != '$' || !cmdInfo->argv[b][1])
			continue;

		if (!_strcmp(cmdInfo->argv[b], "$?"))
		{
			replace_string(&(cmdInfo->argv[b]),
				_strdup(convert_number(cmdInfo->status, 10, 0)));
			continue;
		}
		if (!_strcmp(cmdInfo->argv[b], "$$"))
		{
			replace_string(&(cmdInfo->argv[b]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nde = nde_starts_with(cmdInfo->env, &cmdInfo->argv[b][1], '=');
		if (nde)
		{
			replace_string(&(cmdInfo->argv[b]),
				_strdup(_strchr(nde->strg, '=') + 1));
			continue;
		}
		replace_string(&cmdInfo->argv[b], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Substitutes a string
 * @od: Old string address.
 * @nw: New string
 *
 * Return: 1 if substituted, 0 otherwise
 */

int replace_string(char **od, char *nw)
{
	free(*od);
	*od = nw;
	return (1);
}
