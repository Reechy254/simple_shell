#include "shell.h"

/**
 * cp_strg - copies a string
 * @destn: the destination
 * @src: the source
 *
 * Return: the pointer to a destination
 */

char *cp_strg(char *destn, char *src)
{
	int b = 0;

	if (destn == src || src == 0)
		return (destn);

	while (src[b])
	{
		destn[b] = src[b];
		b++;
	}
	destn[b] = 0;

	return (destn);
}

/**
 * strdup_ - it  duplicates a string to another
 * @dupstrg: the duplicated string
 *
 * Return: the  pointer to a duplicated string
 */

char *strdup_(const char *dupstrg)
{
	int length = 0;
	char *retn;

	if (dupstrg == NULL)
		return (NULL);

	while (*dupstrg++)
		length++;

	retn = malloc(sizeof(char) * (length + 1));

	if (!retn)
		return (NULL)
;
	for (length++; length--;)
		retn[length] = *--dupstrg;

	return (retn);
}

/**
 * _puts - it  prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void _puts(char *str)
{
	int b = 0;

	if (!str)
		return;
	while (str[b] != '\0')
	{
		_putchar(str[i]);
		b++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to be printed
 *
 * Return: 1 when success.
 * error, -1 is returned, and errno is appropriately set.
 */

int _putchar(char c)
{
	static int b;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || b >= WRITE_BUF_SIZE)
	{
		write(1, buf, b);
		b = 0;
	}
	if (c != BUF_FLUSH)
		buf[b++] = c;
	return (1);
}
