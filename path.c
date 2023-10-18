#include "shell.h"

/**
 * is_cmd - Checks if a file is excutable.
 * @info: Info structure
 * @path: File path
 *
 * Return: 1 if excutable, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat s;

	(void)cmdInfo;
	if (!path || stat(path, &s))
		return (0);

	if (s.s_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates characters from strat to stop index.
 * @pathstrg: The PATH string
 * @star: Start index
 * @stp: End index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstrg, int star, int stp)
{
	static char buff[1024];
	int a = 0, b = 0;

	for (b = 0, a = star; a < stp; a++)
		if (pathstrg[a] != ':')
			buff[b++] = pathstrg[a];
	buf[b] = 0;
	return (buff);
}

/**
 * find_path - Locates command in the PATH string
 * @info: Info structure
 * @pathstrg: PATH string
 * @cmd: the command to locate.
 *
 * Return: Full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstrg, char *cmd)
{
	int a = 0, cur_pos = 0;
	char *path;

	if (!pathstrg)
		return (NULL);
	if ((_strlen(cmd) > 2) && stars_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstrg[a] || pathstrg[a] == ':')
		{
			path = dup_chars(pathstrg, cur_pos, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstrg[a])
				break;
			curr_pos = a;
		}
		i++;
	}
	return (NULL);
}
