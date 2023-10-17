#include "shell.h"

/**
 * to_print  - prints to the terminal
 *@strng: the string to be printed
 *
 */

void to_print(const char *strng)
{
	write(STDOUT_FILENO, strng, strlen(strng));
}
