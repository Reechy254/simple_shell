#include "shell.h"

/**
 *read_string - reads the coomand from user and remove new
 * line charcter
 *@strng:  the command to be read.
 *@size: gets the size of the command
 *
 */

void read_string(char *strng, size_t size)
{
	if (fgets(strng, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			to_print("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			to_print("Error reading input.\n");
			exit(EXIT_FAILURE);
		}
	}
	strng[strcspn(strng, "\n")] = '\0';
}
