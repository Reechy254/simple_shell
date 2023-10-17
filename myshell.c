#include "shell.h"

/*
 *main- the entry point of the shell.
 *
 *
 */

int main(void)
{
	char strng[120];

	while (true)
	{
		prompt();
		read_string(strng, sizeof(strng));
		exec_command(strng);
	}

	return (0);
}
