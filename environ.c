#include "shell.h"

/**
 * _env - prints current environment
 * @info: struct contains potential arguments.maintaining constant
 *function prototype.
 * Return: Always 0
 */

int _env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets  value of environment variable
 * @info:  this structure contains potential arguments.
 * @name: env var name
 *
 * Return: the value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *q;

	while (node)
	{
		q = starts_with(node->str, name);
		if (q && *q)
			return (q);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenv -  this Initialize new environment variable,
 *             or modifies existing one
 * @info: this structure containing potential arguments.
 *  Return: Always 0
 */
int _setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenv -  this remove an environment variable
 * @info: contains potential arguments, Used to maintain function prototype.
 * Return: Always 0
 */

int _unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates environment linked list
 * @info: the structure containing potential arguments
 * Return: Always 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

