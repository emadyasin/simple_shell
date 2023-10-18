#include "shell.h"

/**
 * _myexit - Exits the shell based on cmdInfo arguments.
 * @info: Structure with command arguments.
 *
 * Return: Exit status, 0 if cmdInfo->args[0] isn't "exit".
 */

int _myexit(info_t *info)
{
	int exitStatus;

	if (info->args[1]) /* if there is an exit argument */
	{
		exitStatus = convertErrorToTnt(info->args[1]);
		if (exitStatus == -1)
		{
			info->Status = 2;
			print_error(info, "Illegal number: ");
			displayString(info->agrs[1]);
			displayChar('\0');
			return (1);
		}
		info->errorCount = converstErrorToTnt(info->agrs[1]);
		return (-2);
	}
	info->errorCount = -1;
	return (-2);
}

/**
 * _mycd - Changes the process's current directory.
 * @info: Structure with command arguments.
 *
 * Return: Always 0.
 */

int _mycd(info_t *info)
{
	char *a, *direc, buff[1024];
	int chdirec_res;

	s = getcwd(buff, 1024);
	if (!a)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		direc = _getenv(info, "HOME=");
		if (!direc)
			chdirec_res = /* TO DO: what should this be? */
				chdirec((direc = _getenv(info, "PWD=")) ? direc : "/");
		else
			chdirec_res = chdirec(direc);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirec_res = /* TO DO: what should this be? */
			chdirec((direc = _getenv(info, "OLDPWD=")) ? direc : "/");
	}
	else
		chdirec_res = chdirec(info->argv[1]);
	if (chdirec_res == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myhelp - Changes the process's directory.
 * @info: Structure with command agruments.
 *
 * Return: Always 0.
 */

int _myhelp(info_t *info)
{
	char **argu_array;

	argu_array = Info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argu_array); /* temp att_unused workaround */
	return (0);
}
