#include "shell.h"

/**
 * _eputs - prints input string
 * @strg: string to be printed
 *
 * Return: Nothing
 */

void _eputs(char *strg)
{
	int i = 0;

	if (!strg)
		return;

	while (strg[i] != '\0')
	{
		_eputchar(strg[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: character to print
 * @fd: file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and erro set appropriately.
 */

int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - prints input string
 * @strg: string to be printed
 * @fd: file descriptor to write to
 *
 * Return: the number of characters put
 */

int _putsfd(char *strg, int fd)
{
	int i = 0;

	if (!strg)
		return (0);

	while (*strg)
	{
		i += _putfd(*strg++, fd);
	}
	return (i);
}
