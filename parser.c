#include "shell.h"

/**
 * _cmd - checks if the file is an executable command
 * @info: info of the structure
 * @path: the path to the file
 *
 * Return: 1 if true, 0 otherwise
 */

int _cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @start: the  beginning index
 * @strpath: the PATH string
 * @end: the stopping index
 *
 * Return: should return a  pointer to new bufffer
 */
char *dup_chars(char *strpath, int start, int end)
{
	static char buff[1024];
	int b = 0, k = 0;

	for (k = 0, b = start; b < end; b++)
		if (strpath[b] != ':')
			buff[k++] = strpath[b];
	buff[k] = 0;
	return (buff);
}

/**
 * get_path - get  this cmd in the PATH string
 * @strpath:  PATH string
 * @info: the info struct
 * @cmd: the cmd being looked for
 *
 * Return: the full path of the cmd if found or NULL when not found
 */

char *get_path(info_t *info, char *strpath, char *cmd)
{
	int b = 0, curr_pos = 0;
	char *path;

	if (!strpath)
		return (NULL);
	if ((strlen_(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!strpath[b] || strpath[b] == ':')
		{
			path = dup_chars(strpath, curr_pos, b);
			if (!*path)
				strg_concat(path, cmd);
			else
			{
				strg_concat(path, "/");
				strg_concat(path, cmd);
			}
			if (_cmd(info, path))
				return (path);
			if (!strpath[i])
				break;
			curr_pos = b;
		}
		b++;
	}
	return (NULL);
}

