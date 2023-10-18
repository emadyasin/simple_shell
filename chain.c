#include "shell.h"

/**
 * is_chain - Checks if the current character is a chain delimeter
 * @info: command structure
 * @buff: Characture buffer
 * @a: Current position in buffer.
 *
 * Return: 1 if delimeter, 0 otherwise.
 */
int is_chain(info_t *info, char *buff, size_t *a)
{
	size_t k = *a;

	if (buff[k] == '|' && buff[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[k] == ';') /* found end of this command */
	{
		buff[k] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*a = k;
	return (1);
}

/**
 * check_chain - Evaluates chaining continuation based on previous status.
 * @info: Command structure.
 * @buff: Character buffer
 * @a: Current position in buffer.
 * @b: Starting position in buffer.
 * @leng: Buffer length.
 *
 * Return: Void
 */

void check_chain(info_t *info, char *buff,
		size_t *a, size_t b, size_t leng)
{
	size_t k = *a;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[b] = 0;
			k = leng;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[b] = 0;
			k = leng;
		}
	}

	*a = k;
}

/**
 * replace_alias - substitutes aliases in the tokenized string
 * @info: Command structure.
 *
 * Return: 1 if substituted, 0 otherwise.
 */

int replace_alias(Info_t *info)
{
	int b;
	list_t *nde;
	char *a;

	for (b = 0; b < 10; b++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		a = _strchr(node->str, '=');
		if (!a)
			return (0);
		a = _strdup(a + 1);
		if (!a)
			return (0);
		info->argv[0] = a;
	}
	return (1);
}

/**
 * replace_vars - Substitutes variables in the tokenized string
 * @info: Command structure.
 *
 * Return: 1 if substituted, 0 otherwise
 */

int replace_vars(info_t *info)
{
	int b = 0;
	list_t *node;

	for (b = 0; info->argv[b]; b++)
	{
		if (info->argv[b][0] != '$' || !info->argv[b][1])
			continue;

		if (!_strcmp(info->argv[b], "$?"))
		{
			replace_string(&(info->argv[b]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[b], "$$"))
		{
			replace_string(&(info->argv[b]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[b][1], '=');
		if (node)
		{
			replace_string(&(info->argv[b]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[b], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Substitutes a string
 * @old: Old string address.
 * @new: New string
 *
 * Return: 1 if substituted, 0 otherwise
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
