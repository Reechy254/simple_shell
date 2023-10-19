#include "shell.h"

/**
 * _exit - exits shell
 * @info: Structure containing the arguments. maintains function prototype
 * constant function prototype.
 * Return: with given exit status "return exit"
 * (0) if info.argv[0] != "exit"
 */
int _exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = strg_to_int(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = strg_to_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd -  changes the  directory
 * @info: the structur containing potential argum_ents.for prototype
 * Return: Always 0
 */
int _cd(info_t *info)
{
	char *j, *dir, buffer[1024];
	int chdir_ret;

	j = getcwd(buffer, 1024);
	if (!j)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (strcmp_(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(j);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _change - changes current directory of  process
 * @info: Structure that contains potential args.Used in maintaining
 * constant function prototype.
 * Return: Always 0
 */
int _change(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

