#include "shell.h"

/**
 * **to_words - separates words from string.delimiters are ignored
 * @strg: the input string_
 * @d: the delimeter for a string
 * Return: the pointer to an array of strings, or NULL if failed
 */

char **to_words(char *strg, char *d)
{
	int b, g, c, m, numwords = 0;
	char **s;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (b = 0; strg[b] != '\0'; b++)
		if (!the_delim(strg[b], d) && (the_delim(strg[b + 1], d) || !strg[b + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (b = 0, g = 0; g < numwords; g++)
	{
		while (the_delim(strg[b], d))
			b++;
		c = 0;
		while (!the_delim(strg[b + c], d) && strg[b + c])
			c++;
		s[g] = malloc((c + 1) * sizeof(char));
		if (!s[g])
		{
			for (c = 0; c < g; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			s[g][m] = strg[b++];
		s[g][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **to_words - it splits a string into words
 * @strg: the inputed string
 * @d: the delimeter
 * Return: the pointer to an array of strings, or NULL if fails
 *
 */
char **to_words(char *strg, char d)
{
	int b, g, c, m, numwords = 0;
	char **s;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	for (b = 0; strg[b] != '\0'; b++)
		if ((strg[b] != d && strg[b + 1] == d) ||
				    (strg[b] != d && !strg[b + 1]) || strg[b + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (b = 0, g = 0; g < numwords; g++)
	{
		while (strg[b] == d && strg[b] != d)
			b++;
		c = 0;
		while (strg[b + c] != d && strg[b + c] && strg[b + c] != d)
			c++;
		s[g] = malloc((c + 1) * sizeof(char));
		if (!s[g])
		{
			for (c = 0; k < g; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			s[g][m] = strg[b++];
		s[g][m] = 0;
	}
	s[g] = NULL;
	return (s);
}

