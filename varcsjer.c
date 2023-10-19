#include "shell.h"

/**
 * usage - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int usage(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * the_delim - checks if character is a delimeter
 * @c: the character to be check
 * @delim: the delimeter of the string
 * Return: 1 if true, 0 if false
 */

int the_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _alpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if string has no numbers, converted number otherwise
 */

int to_int(char *s)
{
	int b, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (b = 0; s[b] != '\0' && flag != 2; b++)
	{
		if (s[b] == '-')
			sign *= -1;

		if (s[b] >= '0' && s[b] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[b] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

