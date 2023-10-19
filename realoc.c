#include "shell.h"

/**
 * mem_fill - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte that *s to be fill with
 * @n: the numbert of bytes to be filled
 * Return: th (s) value  a pointer to the memory area s
 */

char *mem_fill(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * free_strg - frees a string of strings.
 * @strg_of_strg: the string of strings.
 */

void free_strg(char **strg_of_strg)
{
	char **a = strg_of_strg;

	if (!strg_of_strg)
		return;
	while (*strg_of_strg)
		free(*strg_of_strg++);
	free(a);
}

/**
 * mem_realloc - it reallocates a block of memory
 * @prev_pointer: the pointer to a previously mallocated block.
 * @new_size: the  byte size of a new block
 * @prev_size: the byte size of a previous block
 *
 * Return: the pointer to an old block nameesn.
 */

void *mem_realloc(void *prev_pointer, unsigned int prev_size,
unsigned int new_size)
{
	char *p;

	if (!prev_pointer)
		return (malloc(new_size));
	if (!new_size)
		return (free(prev_pointer), NULL);
	if (new_size == prev_size)
		return (prev_pointer);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		p[prev_size] = ((char *)prev_pointer)[prev_size];
	free(prev_pointer);
	return (p);
}

