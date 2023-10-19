#include "shell.h"

/**
 * _history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info:this struct contais potential argument for constant function prottype.
 *  Return: 0 always
 */

int _history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * alias_to_string - sets alias to string
 * @info: the  parameter structure
 * @strg:  string alias
 *
 * Return: success 0,  error 1.
 */

int alias_to_string(info_t *info, char *strg)
{
	char *q, s;
	int ret;

	q = strgchr(strg, '=');
	if (!q)
		return (1);
	s = *q;
	*q = 0;
	ret = del_indexnode(&(info->alias),
		get_node_index(info->alias, prefix_node(info->alias, strg, -1)));
	*q = s;
	return (ret);
}

/**
 * set_alias - this code  sets alias to string
 * @info: this is the parameter structure
 * @strg: string alias
 *
 * Return: on success 0, on error 1
 */

int set_alias(info_t *info, char *strg)
{
	char *q;

	p = strgchr(strg, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (alias_to_string(info, strg));

	alias_to_string(info, strg);
	return (add_node_end(&(info->alias), strg, 0) == NULL);
}

/**
 * print_alias -  this prints an alias string in the code
 * @node: alias node
 *
 * Return: on success 0, 1 on error
 */

int print_alias(list_t *node)
{
	char *q = NULL, *b = NULL;

	if (node)
	{
		q = strgchr(node->strg, '=');
		for (b = node->strg; b <= q; b++)
		_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - mimics the alias builtin (man alias)
 * @info: the structure containing arguments.  to maintain function prototype.
 *  Return: Always 0
 */

int _alias(info_t *info)
{
	int i = 0;
	char *q = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		q = strgchr(info->argv[i], '=');
		if (q)
			set_alias(info, info->argv[i]);
		else
			print_alias(prefix_node(info->alias, info->argv[i], '='));
	}

	return (0);
}
