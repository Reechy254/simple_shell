#include "shell.h"

/**
 * get_env - returns the string array copy of our environment
 * @info: Struct that contains potential arguments.which maintains
 *          constant function prototype.
 * Return: Always 0
 */

char **get_env(info_t *info)
{
	if (!info->env || info->env_changed)
	{
		info->env = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->env);
}

/**
 *_unsetenv - Removes environment variable
 *@info: Structure that contains potential arguments. Used to maintain
 *        constant function prototype.
 *Return: 1 on delete, 0 otherwise
 *@strgenv_var: the string env variable property
 */

int _unsetenv(info_t *info, char *strgenv_var)
{
	list_t *node = info->env;
	size_t b = 0;
	char *p;

	if (!node || !strgenv_var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, strgenv_var);
		if (p && *p == '=')
		{
			info->env_changed = del_indexnode(&(info->env), b);
			b = 0;
			node = info->env;
			continue;
		}

		node = node->next;
		b++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initiates new environment variable,or modefys existing one
 * @info: Structure containing potential arguments used to maintain
 *        constant function prototype.
 * @strgenv_var: the string environment variable property
 * @value: the string environment variabl value
 *  Return: Always 0
 */

int _setenv(info_t *info, char *strgenv_var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *c;

	if (!strgenv_var || !value)
		return (0);

	buff = malloc(strlen_(strgenv_var) + strlen_(value) + 2);
	if (!buff)
		return (1);

	cp_strg(buff, strgenv_var);
	strg_concat(buff, "=");
	strg_concat(buff, value);
	node = info->env;

	while (node)
	{
		c = starts_with(node->str, strgenv_var);

		if (c && *c == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}

		node = node->next;
	}

	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
