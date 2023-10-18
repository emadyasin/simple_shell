#include "shell.h"

/**
 * get_history_file - Retrieves the history file
 * @cmdInfo: Pointer to the parameter structure
 *
 * Return: Pointer to the allocated history file string.
 */

char *get_history_file(cmdInfo_t *cmdInfo)
{
	char *buff, *direc;

	direc = _getenv(cmdInfo, "HOME=");
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
 * @cmdInfo: Pointer to  the parameter structure
 *
 * Return: 1 on success, -1 otherwise.
 */
int write_history(cmdInfo_t *cmdInfo)
{
	ssize_t fid;
	char *filenam = get_history_file(cmdInfo);
	list_t *nod = NULL;

	if (!filenam)
		return (-1);

	fid = open(filenam, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenam);
	if (fid == -1)
		return (-1);
	for (nod = cmdInfo->history; nod; nod = nod->next)
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
 * @cmdInfo: Pointer to  the parameter struct.
 *
 * Return: Histcount on success, 0 otherwise.
 */

int read_history(cmdInfo_t *cmdInfo)
{
	int k, las = 0, licount = 0;
	ssize_t fid, readlen, fisize = 0;
	struct stat sta;
	char *buff = NULL, *filenam = get_history_file(mdInfo);

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
			build_history_list(cmdInfo, buff + las, licount++);
			las = k + 1;
		}
	if (las != k)
		build_history_list(cmdInfo, buff + las, licount++);
	free(buff);
	cmdInfo->histcount = linecount;
	while (cmdInfo->histcount-- >= HIST_MAX)
		delete_nod_at_index(&(cmdInfo->history), 0);
	renumber_history(cmdInfo);
	return (cmdInfo->histcount);
}

/**
 * build_history_list - Adds an entry to a history linked list.
 * @cmdInfo: Pointer to the parameter structure.
 * @buff: Input buffer.
 * @licount: History linecount.
 *
 * Return: Always 0
 */

int build_history_list(cmdInfo_t *cmdInfo, char *buff, int licount)
{
	list_t *nod = NULL;

	if (cmdInfo->history)
		nod = cmdInfo->history;
	add_nod_end(&nod, buff, licount);

	if (!cmdInfo->history)
		cmdInfo->history = nod;
	return (0);
}

/**
 * renumber_history - Renumbers the history list after modification.
 * @cmdInfo: Pointer to the parameter Structure.
 *
 * Return: Update histcount
 */

int renumber_history(cmdInfo_t *cmdInfo)
{
	list_t *nod = cmdInfo->history;
	int K = 0;

	while (nod)
	{
		nod->numb = i++;
		nod = nod->next;
	}
	return (cmdInfo->histcount = k);
}
