#include "shell.h"

/**
 * clear_info -Initializes cmdInfo_t structure.
 * @cmdInfo: Pointer to the structure.
 */
void clear_info(cmdInfo_t *cmdInfo)
{
	cdmInfo->arg = NULL;
	cmdInfo->argv = NULL;
	cmdInfo->path = NULL;
	cmdInfo->argc = 0;
}

/**
 * set_info - Initializes info_t structure with argument vector.
 * @cmdInfo: Pointer to the structure
 * @avec: Argument vector
 */
void set_info(cmdInfo_t *cmdInfo, char **avec)
{
	int a = 0;

	cmdInfo->fname = avec[0];
	if (cmdInfo->arg)
	{
		cmdInfo->argv = strtow(cmdInfo->arg, " \t");
		if (!cmdInfo->argv)
		{

			cmdInfo->argv = malloc(sizeof(char *) * 2);
			if (cmdInfo->argv)
			{
				cmdInfo->argv[0] = _strdup(info->arg);
				cmdInfo->argv[1] = NULL;
			}
		}
		for (a = 0; cmdInfo->argv && cmdInfo->argv[a]; i++)
			;
		cmdInfo->argc = a;

		replace_alias(cmdInfo);
		replace_vars(cmdInfo);
	}
}

/**
 * free_info - Frees fields f the cmdInfo_t structure.
 * @cmdInfo: Pointer t the structure.
 * @al: If true. frees  all fields
 */
void free_info(cmdInfo_t *cmdInfo, int al)
{
	ffree(cmdInfo->argv);
	cmdInfo->argv = NULL;
	cmdInfo->path = NULL;
	if (al)
	{
		if (!cmdInfo->cmd_buf)
			free(cmdInfo->arg);
		if (cmdInfo->env)
			free_list(&(cmdInfo->env));
		if (cmdInfo->history)
			free_list(&(cmdInfo->history));
		if (cmdInfo->alias)
			free_list(&(cmdInfo->alias));
		ffree(cmdInfo->environ);
			cmdInfo->environ = NULL;
		bfree((void **)cmdInfo->cmd_buf);
		if (cmdInfo->readfd > 2)
			close(cmdInfo->readfd);
		_putchar(BUF_FLUSH);
	}
}
