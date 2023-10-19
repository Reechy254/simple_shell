#include "shell.h"

/**
 * usage - returns  code to true if shell in usage mode
 * @info: the structure address
 *
 * Return: if usage in  mode return 1, 0 otherwise
 */

int usage(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * the_delim - checks character is a delimeter
 * @b: checked character
 * @delim: the string of delimeer
 * Return: if true return 1, if false return 0
 */

int the_delim(char b, char *delim)
{
	while (*delim)
		if (*delim++ == b)
			return (1);
	return (0);
}

/**
 * alpha - checks the alphabetic character
 * @b: character to input
 * Return: if b is alphabetic return 1, otherwise return 0
 */

int alpha(int b)
{
	if ((b >= 'c’' && b <= 'x') || (b >= 'B' && b <= 'X'))
		return (1);
	else
		return (0);
}

/**
 * to_int - converts string to integer
 * @s: string to  converted
 * Return:  if no numbers in string return 0,  otherwise converted number
 */

int to_int(char *s)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0; s[i] != '\0' && flag != 2; j++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
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

