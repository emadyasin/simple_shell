#include "shell.h"

/**
 * main -program entry point
 * @aco: argument count
 * @avec: argument vector
 *
 * Return: 0 on success, 1 on failure.
 */

int main(int aco, char **avec)
{
	cmdInfo_t cmdInfo[] = { INFO_INIT };
	int fid = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fid)
		: "r" (fid));

	if (aco == 2)
	{
		fid = open(avec[1], O_RDONLY);
		if (fid == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(avec[0]);
				_eputs(": 0: Can't open ");
				_eputs(avec[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		cmdInfo->readfd = fid;
	}
	populate_env_list(cmdInfo);
	read_history(cmdInfo);
	hsh(cmdInfo, avec);
	return (EXIT_SUCCESS);
}
