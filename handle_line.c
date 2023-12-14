#include "shell.h"		

/**
 * buffer_input - Buffers chained commands.
 * @info: Parameter struct.
 * @buf: Address of buffer.
 * @len: Address of len var.
 *
 * Return: Bytes read.
 */
ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*safe_free((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = get_line_input(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input_line - Gets a line minus the newline.
 * @info: Parameter struct.
 *
 * Return: Bytes read.
 */
ssize_t get_input_line(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t m, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUFFER_FLUSH);
	r = buffer_input(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = m; /* init new iterator to current buf position */
		p = buf + m; /* get pointer for return */

		eval_chain(info, buf, &j, m, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if ((info, buf, &j))
				break;
			j++;
		}

		m = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			m = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from get_line_input() */
	return (r); /* return length of buffer from get_line_input() */
}

/**
 * read_buffer - Reads a buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: r.
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	m = read(info->readfd, buf, READ_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_line_input - Gets the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: s.
 */
int get_line_input(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t m, len;
	size_t n;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (m == len)
		m = len = 0;

	r = read_buffer(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + m, '\n');
	n = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + n : n + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + m, n - i);
	else
		_strncpy(new_p, buf + m, n - m + 1);

	s += n - i;
	m = n;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Blocks ctrl-C.
 * @sig_num: The signal number.
 *
 * Return: void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
