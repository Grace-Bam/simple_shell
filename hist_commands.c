#include "shell.h"

/**
 * history_file - Retrieves the history file path.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file path.
 */

char *history_file(info_t *info)
{
	char *buf, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist - Creates a file or appends to an existing file for history.
 * @info: Parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_hist(info_t *info)
{
	ssize_t fd;
	char *filename = history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		custom_putsfd(node->str, fd);
		custom_putfd('\n', fd);
	}
	custom_putfd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - Reads history from file and updates the history linked list.
 * @info: Parameter struct.
 *
 * Return: Number of history entries on success, 0 on failure.
 */
int read_hist(info_t *info)
{
	int m, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (m = 0; m < fsize; m++)
		if (buf[m] == '\n')
		{
			buf[m] = 0;
			history_list(info, buf + last, linecount++);
			last = m + 1;
		}
	if (last != m)
		history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	re_number_hist(info);
	return (info->histcount);
}

/**
 * history_list - Adds an entry to the history linked list.
 * @info: Parameter struct.
 * @buf: Buffer containing the history entry.
 * @linecount: Line count of the history entry.
 *
 * Return: Always 0.
 */
int history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	_addnode_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * re_number_hist - Renumbers the history linked list after changes.
 * @info: Parameter struct.
 *
 * Return: The new histcount.
 */
int re_number_hist(info_t *info)
{
	list_t *node = info->history;
	int m = 0;

	while (node)
	{
		node->num = m++;
		node = node->next;
	}
	return (info->histcount = m);
}
