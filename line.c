#include "shell.h"

/**
 * input_buff - the  buffers chained commands
 * @info: the parameter structure
 * @buff: the address to the  buffer
 * @len: address of the len variable
 *
 * Return: bytes read
 */

ssize_t input_buff(info_t *info, char **buff, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;

		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = getline_(info, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}

			info->linecount_flag = 1;
			rem_comments(*buff);
			histo_ls_entry(info, *buff, info->histcount++);

			{
				*len = r;
				info->cmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line without the newline
 * @info: struct  parameter
 *
 * Return: bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buff_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buff(info, &buff, &len);

	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buff + i;

		check_chain(info, buff, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buff_type = CMD_NORM;
		}

		*buff_p = p;
		return (strlen_(p));
	}

	*buff_p = buff;
	return (r);
}

/**
 * read_buff - reads  buffer
 * @info: parameter struct
 * @buff: the  buffer
 * @s: the  size
 *
 * Return: r
 */

ssize_t read_buff(info_t *info, char *buff, size_t *s)
{
	ssize_t r = 0;

	if (*s)
		return (0);
	r = read(info->readfd, buff, READ_BUF_SIZE);
	if (r >= 0)
		*s = r;
	return (r);
}

/**
 * getline_ - gets next line of  input from the Standard input
 * @info: the  parameter struct
 * @ptr: address of a pointer to the buffer, preallocated or NULL
 * @ptr_length: size of a  preallocated ptr buffer when not NULL
 *
 * Return: s
 */

int getline_(info_t *info, char **ptr, size_t *ptr_length)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && ptr_length)
		s = *ptr_length;

	if (i == len)
		i = len = 0;

	r = read_buff(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = strgchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = mem_realloc(p, s, s ? s + k : k + 1);

	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		strg_concat(new_p, buff + i, k - i);
	else
		cp_strg(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (ptr_length)
		*ptr_length = s;

	*ptr = p;

	return (s);
}

/**
 * sigintHandler -it blocks the ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

