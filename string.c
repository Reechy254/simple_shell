#include "shell.h"

/**
 * strlen_ - gets the total length of a string
 * @strg: string whose length to be checked
 *
 * Return: the integeral length of the string
 */

int strlen_(char *strg)
{
	int b = 0;

	if (!i)
		return (0);

	while (*i++)
		b++;
	return (b);
}

/**
 * strcmp_ - it performs comparison of two strangs.
 * @strang1: this the first strang
 * @strang2: this the second strang
 *
 * Return: negative value if 1 is less than 2
 * positive if strang1 > strang2, zero if strang1 == strang2
 */

int strcmp_(char *strang1, char *strang2)
{
	while (*strang1 && *strang2)
	{
		if (*strang1 != *strang2)
			return (*strang1 - *strang2);
		strang1++;
		strang2++;
	}
	if (*strang1 == *strang2)
		return (0);
	else
		return (*strang1 < *strang2 ? -1 : 1);
}

/**
 * starts_with - checks if substring starts with the string
 * @find_strg: the string to be search
 * @sub_string:  the substring to be found
 *
 * Return: the address of next character of the string or NULL
 */

char *starts_with(const char *find_strg, const char *sub_string)
{
	while (*sub_string)
		if (*sub_string++ != *find_strg++)
			return (NULL);
	return ((char *)find_strg);
}

_/**
 * strg_concat - it concatenates the two strings in the function
 * @buff_destn: the buff_destnination buffer
 * @buff_src: the source buffer
 *
 * Return: pointer to destination of the buffer
 */

char *strg_concat(char *buff_destn, char *buff_src)
{
	char *ret = buff_destn;

	while (*buff_destn)
		buff_destn++;
	while (*buff_src)
		*buff_destn++ = *buff_src++;
	*buff_destn = *buff_src;
	return (ret);
}

