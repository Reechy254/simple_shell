#include "shell.h"

/**
 *setfree - releases a pointer and nulifiess the address
 * @addrs: address of the pointer to free
 *
 * Return: 1 if released, otherwise 0.
 */

int setfree(void **addrs)
{
	if (addrs && *addrs)
	{
		free(*addrs);
		*addrs = NULL;
		return (1);
	}

	return (0);
}

