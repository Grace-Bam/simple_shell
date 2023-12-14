#include "shell.h"

/**
 * hsh - Main shell loop.
 * @info: Parameter and return info struct.
 * @av: Argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_result = 0;

	while (r != -1 && builtin_result != -2)
	{
		clear_info(info);
		if (interactive_mode(info))
			_puts("$ ");
		custom_putchar(BUFFER_FLUSH);
		r = get_input_line(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_result = get_builtin(info);
			if (builtin_result == -1)
				get_cmd(info);
		}
		else if (interactive_mode(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_hist(info);
	free_info(info, 1);
	if (!interactive_mode(info) && info->status)
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_result);
}

/**
 * get_builtin - Finds a builtin command.
 * @info: Parameter and return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         2 if builtin signals exit().
 */
int get_builtin(info_t *info)
{
	int m, built_in_result = -1;
	builtin_t builtintbl[] = {
		{"exit", shell_exit},
		{"env", print_env},
		{"help", _help},
		{"history", _history},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", _cd},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	for (m = 0; builtintbl[m].type; m++)
		if (_strcmp(info->argv[0], builtintbl[m].type) == 0)
		{
			info->line_count++;
			built_in_result = builtintbl[m].func(info);
			break;
		}
	return (built_in_result);
}

/**
 * get_cmd - Finds a command in PATH.
 * @info: Parameter and return info struct.
 *
 * Return: void.
 */
void get_cmd(info_t *info)
{
	char *path = NULL;
	int m, n;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (m = 0, n = 0; info->arg[m]; m++)
		if (!check_delim(info->arg[m], " \t\n"))
			n++;
	if (!n)
		return;

	path = get_path(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive_mode(info) || get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && cmd_exe(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			display_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks an exec thread to run a command.
 * @info: Parameter and return info struct.
 *
 * Return: void.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				display_error(info, "Permission denied\n");
		}
	}
}
