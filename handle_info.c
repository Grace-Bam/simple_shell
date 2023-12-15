#include "shell.h"

/**
 * clear_info - Initializes an info_t struct.
 * @info: Pointer to the struct to be initialized.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes an info_t struct with the given argument vector.
 * @info: Pointer to the struct to be initialized.
 * @av: Argument vector.
 */
void set_info(info_t *info, char **av)
{
	int m = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_tow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (m = 0; info->argv && info->argv[m]; m++)
			;
		info->argc = m;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees fields of an info_t struct.
 * @info: Pointer to the struct containing fields to be freed.
 * @all: True if freeing all fields.
 */
void free_info(info_t *info, int all)
{
	free_f(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			len_list(&(info->env));
		if (info->history)
			len_list(&(info->history));
		if (info->alias)
			len_list(&(info->alias));
		free_f(info->environ);
			info->environ = NULL;
		safe_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFFER_FLUSH);
	}
}
