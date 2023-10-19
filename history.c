#include "shell.h"

/**
 * get_histo_file - tries to get the histo file.
 * @info: the parameter structure
 *
 * Return: the string allocated which contains the histo file
 */

char *get_histo_file(info_t *info)
{
	char *buff, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (strlen_(dir) + strlen_(HIST_FILE) + 2));
	if (!buff)
		return (NULL);

	buff[0] = 0;
	cp_strg(buff, dir);
	strg_concat(buff, "/");
	strg_concat(buff, HIST_FILE);

	return (buff);
}

/**
 * write_histo - creates or appends to an existing file of histo
 * @info: the parameter strucure
 *
 * Return: 1 on success, else -1
 */
int write_histo(info_t *info)
{
	ssize_t fd;
	char *filename = get_histo_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_histo - reads the history from a file
 * @info: the parameter struct
 *
 * Return: the history's count on success, else 0
 */

int read_histo(info_t *info)
{
	int b, last = 0, histo_line_count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_histo_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);

	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (b = 0; b < fsize; b++)
		if (buff[b] == '\n')
		{
			buff[b] = 0;
			histo_ls_entry(info, buff + last, histo_line_count++);
			last = b + 1;
		}
	if (last != b)
		histo_ls_entry(info, buff + last, histo_line_count++);
	free(buff);
	info->histcount = histo_line_count;

	while (info->histcount-- >= HIST_MAX)
		del_indexnode(&(info->history), 0);
	renum_histo(info)
	return (info->histcount);
}

/**
 * histo_ls_entry - creates  entry to a histo linked list
 * @info: the structure containing potential argument, used in maintaining
 * @buff: buffer
 * @histo_line_count: the history linecount, history count
 *
 * Return: Always 0
 */

int histo_ls_entry(info_t *info, char *buff, int histo_line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buff, histo_line_count);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renum_histo - renumbers history linked list after changes done
 * @info: Structure containing potential arguments, used for maintainance
 *
 * Return: the new historycount
 */

int renum_histo(info_t *info)
{
	list_t *node = info->history;
	int b = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount b);
}

