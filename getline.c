#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buff: address of buffer
 * @leng: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buff, size_t *leng)
{
	ssize_t a = 0;
	size_t leng_p = 0;

	if (!*leng) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)cmdInfo->cmd_buff);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buff, &leng_p, stdin);
#else
		a = _getline(info, buff, &leng_p);
#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buff)[a - 1] = '\0'; /* remove trailing newline */
				a--;
			}
			info->licount_flag = 1;
			remove_comments(*buff);
			build_history_list(info, *buff, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*leng = a;
				info->cmd_buff = buff;
			}
		}
	}
	return (a);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t k, m, leng;
	ssize_t a = 0;
	char **buff_p = &(info->arg), *p;

	_putchar(BUFF_FLUSH);
	a = input_buff(info, &buff, &leng);
	if (a == -1) /* EOF */
		return (-1);
	if (leng)	/* we have commands left in the chain buffer */
	{
		m = k; /* init new iterator to current buf position */
		p = buff + k; /* get pointer for return */

		check_chain(info, buff, &m, k, leng);
		while (m < leng) /* iterate to semicolon or end */
		{
			if (is_chain(info, buff, &m))
				break;
			m++;
		}

		k = m + 1; /* increment past nulled ';'' */
		if (k >= leng) /* reached end of buffer? */
		{
			k = leng = 0; /* reset position and length */
			info->cmd_buff_type = CMD_NORM;
		}

		*buff_p = p; /* pass back pointer to current command position */
		return (_strleng(p)); /* return length of current command */
	}

	*buff_p = buff; /* else not a chain, pass back buffer from _getline() */
	return (a); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @k: size
 *
 * Return: a
 */
ssize_t read_buf(info_t *info, char *buff, size_t *k)
{
	ssize_t a = 0;

	if (*k)
		return (0);
	a = read(info->readfid, buff, READ_BUFF_SIZE);
	if (a >= 0)
		*k = a;
	return (a);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @pt: address of pointer to buffer, preallocated or NULL
 * @leng: size of preallocated ptr buffer if not NULL
 *
 * Return: m
 */
int _getline(info_t *info, char **pt, size_t *leng)
{
	static char buff[READ_BUFF_SIZE];
	static size_t k, leng;
	size_t l;
	ssize_t a = 0, m = 0;
	char *p = NULL, *new_p = NULL, *d;

	p = *pt;
	if (p && leng)
		m = *leng;
	if (k == leng)
		k = leng = 0;

	a = read_buff(info, buff, &leng);
	if (a == -1 || (a == 0 && leng == 0))
		return (-1);

	d = _strchr(buff + k, '\n');
	l = d ? 1 + (unsigned int)(d - buff) : leng;
	new_p = _realloc(p, m, m ? m + l : l + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (m)
		_strncat(new_p, buff + k, l - k);
	else
		_strncpy(new_p, buff + k, l - k + 1);

	m += kl - k;
	k = l;
	p = new_p;

	if (leng)
		*leng = s;
	*pt = p;
	return (m);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_n: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}
