#include "shell.h"

/**
 * _myexit - Exits the shell based on cmdInfo arguments.
 * @cmdInfo: Structure with command arguments.
 *
 * Return: Exit status, 0 if cmdInfo->args[0] isn't "exit".
 */

int _myexit(cmdInfo_t *cmdInfo)
{
	int exitStatus;

	if (cmdInfo->args[1]) /* if there is an exit argument */
	{
		exitStatus = convertErrorToTnt(cmdInfo->args[1]);
		if (exitStatus == -1)
		{
			cmdInfo->Status = 2;
			print_error(cmdInfo, "Illegal number: ");
			displayString(cmdInfo->agrs[1]);
			displayChar('\0');
			return (1);
		}
		cmdInfo->errorCount = converstErrorToTnt(cmdInfo->agrs[1]);
		return (-2);
	}
	cmdInfo->errorCount = -1;
	return (-2);
}

/**
 * _mycd - Changes the process's current directory.
 * @cmdInfo: Structure with command arguments.
 *
 * Return: Always 0.
 */

int _mycd(cmdInfo_t *cmdInfo)
{
	char *a, *direc, buf[1024];
	int chdirec_res;

	s = getcwd(buf, 1024);
	if (!a)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!cmdInfo->argv[1])
	{
		direc = _getenv(cmdInfo, "HOME=");
		if (!direc)
			chdirec_res = /* TODO: what should this be? */
				chdirec((direc = _getenv(cmdInfo, "PWD=")) ? direc : "/");
		else
			chdirec_res = chdirec(direc);
	}
	else if (_strcmp(cmdInfo->argv[1], "-") == 0)
	{
		if (!_getenv(cmdInfo, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(cmdInfo, "OLDPWD=")), _putchar('\n');
		chdirec_res = /* TODO: what should this be? */
			chdirec((direc = _getenv(cmdInfo, "OLDPWD=")) ? direc : "/");
	}
	else
		chdirec_res = chdirec(cmdInfo->argv[1]);
	if (chdirec_res == -1)
	{
		print_error(cmdInfo, "can't cd to ");
		_eputs(cmdInfo->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(cmdInfo, "OLDPWD", _getenv(cmdInfo, "PWD="));
		_setenv(cmdInfo, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _myhelp - Changes the process's directory.
 * @cmdInfo: Structure with command agruments.
 *
 * Return: Always 0.
 */

int _myhelp(cmdInfo_t *cmdInfo)
{
	char **argu_array;

	argu_array = cmdInfo->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argu_array); /* temp att_unused workaround */
	return (0);
}
