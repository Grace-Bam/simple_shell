#include "shell.h"

/**
 * cmd_exe - Determines if a file is an executable command.
 *
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if the file is executable, 0 otherwise.
 */
int cmd_exe(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _dupchars - Duplicates characters from a given range in the PATH string.
 *
 * @pathstr: The PATH string.
 * @start: Starting index of the range to duplicate.
 * @stop: Stopping index (exclusive) of the range to duplicate.
 *
 * Return: A pointer to a new buffer containing the duplicated characters.
 */
char *_dupchars(char *pathstr, int start, int stop)
{
	static char buf[1024]; /* Buffer to store duplicated characters */
	int m = 0, n = 0; /* Loop counters for source and destination */

	for (n = 0, m = start; m < stop; m++)
	{
		if (pathstr[m] != ':')
		{
			buf[n++] = pathstr[m];
		}
	}

	buf[n] = 0; /* Null-terminate the buffer to create a valid string */
	return (buf);
}

/**
 * get_path - Finds the full path of a command in the PATH string.
 *
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: The full path of the command if found, otherwise NULL.
 */
char *get_path(info_t *info, char *pathstr, char *cmd)
{
	int m = 0; /* Loop counter for iterating through pathstr */ 
	current_position = 0; /* Stores the starting index of each path segment */
	char *path; /* Buffer to store the current path segment */

	/* Check if pathstr is NULL */
	if (!pathstr)
		return (NULL);

	/* Check if the command starts with "./" and is executable */
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (cmd_exe(info, cmd))
			return (cmd);
	}

	/* Iterate through pathstr to search for the command */
	while (1)
	{
		/* Check for the end of path segment or end of PATH string */
		if (!pathstr[m] || pathstr[m] == ':')
		{
			/* Duplicate the current path segment */
			path = _dupchars(pathstr, current_position, m);

			/* Check if the duplicated path is empty */
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			/* Check if the command is executable at the current path */
			if (cmd_exe(info, path))
				return (path);

			 /* Check if the end of PATH string is reached */
			if (!pathstr[m])
				break;

			/* Update the starting index of the next path segment */
			current_position = m;
		}
		m++;
	}

	/* Command not found in PATH, return NULL */
	return (NULL);
}
