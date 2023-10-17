#include "shell.h"

/**
 *exec_command - creates a chid process to excute user command
 *@strng: the user input
 *
 */

void exec_command(const char *strng)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		to_print("Error forking process.\n");
		exit(EXIT_FAILURE);
	}

	else if (child_pid == 0)
	{
		char *args[128];
		int arg_count = 0;

		char *token = strtok((char *)strng, " ");

		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}

		args[arg_count] = NULL;
		execvp(args[0], args);

		to_print("Error executing command.\n");
		exit(EXIT_FAILURE);
	}

	else
	{
		wait(NULL);
	}
}

