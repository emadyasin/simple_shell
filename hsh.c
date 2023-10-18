#include "shell.h"

/**
 * hsh - main shell loop
 * @cmdInfo: the parameter & return info struct
 * @avec: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(cmdInfo_t *cmdInfo, char **avec)
{
	ssize_t a = 0;
	int builtin_res = 0;

	while (a != -1 && builtin_res != -2)
	{
		clear_cmdInfo(cmdInfo);
		if (interactive(cmdInfo))
			_puts("$ ");
		_eputchar(BUFF_FLUSH);
		a = get_input(cmdInfo);
		if (a != -1)
		{
			set_cmdInfo(cmdInfo, avec);
			builtin_res = find_builtin(cmdInfo);
			if (builtin_res == -1)
				find_cmd(cmdInfo);
		}
		else if (interactive(cmdInfo))
			_putchar('\n');
		free_cmdInfo(cmdInfo, 0);
	}
	write_history(cmdInfo);
	free_cmdInfo(cmdInfo, 1);
	if (!interactive(cmdInfo) && cmdInfo->status)
		exit(cmdInfo->status);
	if (builtin_res == -2)
	{
		if (cmdInfo->err_num == -1)
			exit(cmdInfo->status);
		exit(cmdInfo->err_num);
	}
	return (builtin_res);
}

/**
 * find_builtin - finds a builtin command
 * @cmdInfo: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(cmdInfo_t *cmdInfo)
{
	int k, built_in_res = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (k = 0; builtintbl[k].type; k++)
		if (_strcmp(cmdInfo->argv[0], builtintbl[k].type) == 0)
		{
			cmdInfo->line_count++;
			built_in_res = builtintbl[k].func(cmdInfo);
			break;
		}
	return (built_in_res);
}

/**
 * find_cmd - finds a command in PATH
 * @cmdInfo: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(cmdInfo_t *cmdInfo)
{
	char *pat = NULL;
	int k, l;

	cmdInfo->pat = cmdInfo->argv[0];
	if (cmdInfo->linecount_flag == 1)
	{
		cmdInfo->line_count++;
		cmdInfo->linecount_flag = 0;
	}
	for (k = 0, l = 0; cmdInfo->arg[k]; k++)
		if (!is_delim(cmdInfo->arg[k], " \t\n"))
			l++;
	if (!l)
		return;

	pat = find_path(cmdInfo, _getenv(cmdInfo, "PAT="), cmdInfo->argv[0]);
	if (pat)
	{
		cmdInfo->pat = pat;
		fork_cmd(cmdInfo);
	}
	else
	{
		if ((interactive(cmdInfo) || _getenv(cmdInfo, "PAT=")
			|| cmdInfo->argv[0][0] == '/') && is_cmd(cmdInfo, cmdInfo->argv[0]))
			fork_cmd(cmdInfo);
		else if (*(cmdInfo->arg) != '\n')
		{
			cmdInfo->status = 127;
			print_error(cmdInfo, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @cmdInfo: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(cmdInfo_t *cmdInfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TO DO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(cmdInfo->pat, cmdInfo->argv, get_environ(cmdInfo)) == -1)
		{
			free_cmdInfo(cmdInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TO DO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(cmdInfo->status));
		if (WIFEXITED(cmdInfo->status))
		{
			cmdInfo->status = WEXITSTATUS(cmdInfo->status);
			if (cmdInfo->status == 126)
				print_error(cmdInfo, "Permission denied\n");
		}
	}
}
