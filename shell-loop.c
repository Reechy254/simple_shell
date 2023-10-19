#include "shell.h"

/**
 * jsh - the main shell loop
 * @info: it is the parameter & the return info struct
 * @arg_vector: arguments vector from the main()
 *
 * Return: 0 on success, 1 on error, or error code
 */

int jsh(info_t *info, char **arg_vector)
{
	ssize_t j = 0;
	int builtin_ret = 0;

	while (j != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (usage(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		j = get_input(info);
		if (j != -1)
		{
			set_info(info, arg_vector);
			builtin_ret = get_builtin(info);
			if (builtin_ret == -1)
				get_cmd(info);
		}
		else if (usage(info))
			_putchar('\n');
		release_info(info, 0);
	}
	write_histo(info);
	release_info(info, 1);
	if (!usage(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * get_builtin - finds a builtin command
 * @info: this is the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if the builtin has been executed successfully,
 * 1 if the builtin was found but not successful,
 * 2 if the builtin has signals exit()
 */

int get_builtin(info_t *info)
{
	int b, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _exit},
		{"env", _env},
		{"help", _change},
		{"history", _history},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (b = 0; builtintbl[i].type; b++)
		if (strcmp_(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * get_cmd - to get a command in the PATH
 * @info: the parameter & return info structure
 *
 * Return: void
 */

void get_cmd(info_t *info)
{
	char *path = NULL;
	int b, c;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (b = 0, c = 0; info->arg[b]; b++)
		if (!the_delim(info->arg[i], " \t\n"))
			c++;
	if (!c)
		return;

	path = get_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_process(info);
	}
	else
	{
		if ((usage(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && _cmd(info, info->argv[0]))
			fork_process(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_process - the forks for an execution thread to run cmd
 * @info: the parameter and return info struct
 *
 * Return: void
 */
void fork_process(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			release_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

