#include "shell.h"

/**
 * init_info - it initializes info_t struct
 * @info: the structs address
 */

void init_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - the  info_t structure initiallizer
 * @info: the  structs address
 * @v: the argument vector
 */

void set_info(info_t *info, char **v)
{
	int b = 0;

	info->fname = v[0];
	if (info->arg)
	{
		info->argv = to_words(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strdup_(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (b = 0; info->argv && info->argv[b]; b++)
			;
		info->argc = b;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * release_info - releases info_t struct fields
 * @info: struct address
 * @freed: true if freeing all fields
 */

void release_info(info_t *info, int freed)
{
	free_strg(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (freed)
	{
		if (!info->cmd_buff)
			free(info->arg);

		if (info->env)
			free_list(&(info->env));

		if (info->history)
			free_list(&(info->history));

		if (info->alias)
			free_list(&(info->alias));

		free_strg(info->environ);
			info->environ = NULL;

		setfree((void **)info->cmd_buff);

		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

