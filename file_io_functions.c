#include "shell.h"

/**
 * get_history_file - Retrieves the history file
 * @info: Pointer to the parameter structure
 *
 * Return: Pointer to the allocated history file string.
 */

char *get_history_file(info_t *info)
{
	char *buff, *direc;

	direc = _getenv(info, "HOME=");
	if (!direc)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(direc) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, direc);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - Write or append to a file.
 * @info: Pointer to  the parameter structure
 *
 * Return: 1 on success, -1 otherwise.
 */
int write_history(info_t *info)
{
	ssize_t fid;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filenam)
		return (-1);

	fid = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fid == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfid(nod->str, fid);
		_putfid('\n', fid);
	}
	_putfid(BUF_FLUSH, fid);
	close(fid);
	return (1);
}

/**
 * read_history - Reads command  history froma  file.
 * @info: Pointer to  the parameter struct.
 *
 * Return: Histcount on success, 0 otherwise.
 */

int read_history(info_t *info)
{
	int k, las = 0, licount = 0;
	ssize_t fid, readlen, fisize = 0;
	struct stat sta;
	char *buff = NULL, *filenam = get_history_file(info);

	if (!filenam)
		return (0);

	fid = open(filenam, O_RDONLY);
	free(filenam);
	if (fid == -1)
		return (0);
	if (!fistat(fid, &sta))
		fisize = sta.sta_size;
	if (fisize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fisize + 1));
	if (!buff)
		return (0);
	readlen = read(fid, buff, fisize);
	buff[fisize] = 0;
	if (readlen <= 0)
		return (free(buff), 0);
	close(fid);
	for (k = 0; k < fisize; k++)
		if (buff[k] == '\n')
		{
			buff[k] = 0;
			build_history_list(info, buff + las, licount++);
			las = k + 1;
		}
	if (las != k)
		build_history_list(info, buff + las, licount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds an entry to a history linked list.
 * @info: Pointer to the parameter structure.
 * @buff: Input buffer.
 * @licount: History linecount.
 *
 * Return: Always 0
 */

int build_history_list(info_t *info, char *buff, int licount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buff, licount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Renumbers the history list after modification.
 * @info: Pointer to the parameter Structure.
 *
 * Return: Update histcount
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int K = 0;

	while (node)
	{
		node->numb = i++;
		node = node->next;
	}
	return (info->histcount = k);
}
