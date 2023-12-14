#include "shell.h"

/**
 * detect_chain_delimiter - Tests if the current char in the buffer is a chain delimiter.
 * @info: The parameter struct.
 * @buf: The char buffer.
 * @position: Address of the current position in buf.
 *
 * Return: 1 if a chain delimiter, 0 otherwise.
 */
int detect_chain_delimiter(info_t *info, char *buf, size_t *pos)
{
	size_t index = *pos;

	if (buf[index] == '|' && buf[index + 1] == '|')
	{
		buf[index] = 0;
		index++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[index] == '&' && buf[index + 1] == '&')
	{
		buf[index] = 0;
		index++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[index] == ';')
	{
		buf[index] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = index;
	return (1);
}

/**
 * eval_chain - Checks if we should continue chaining based on the last status.
 * @info: The parameter struct.
 * @buf: The char buffer.
 * @position: Address of the current position in buf.
 * @start: Starting position in buf.
 * @length: Length of buf.
 *
 * Return: Void.
 */
void eval_chain(info_t *info, char *buf, size_t *pos, size_t start, size_t len)
{
	size_t index = *pos;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[start] = 0;
			index = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[start] = 0;
			index = length;
		}
	}

	*pos = index;
}

/**
 * substitute_aliases - Replaces aliases in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int substitute_aliases(info_t *info)
{
	int i;
	list_t *node;
	char *value;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		value = _strchr(node->str, '=') + 1;
		info->argv[0] = _strdup(value);
		if (!info->argv[0])
			return (0);
	}
	return (1);
}

/**
 * substitute_variables - Replaces variables in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int substitute_variables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string_content(&(info->argv[i]),
					_strdup(convert_to_string(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string_content(&(info->argv[i]),
					_strdup(convert_to_string(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string_content(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string_content(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string_content - Replaces the content of a string.
 * @old: Address of the old string.
 * @new_content: New content.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string_content(char **old, char *new_content)
{
	free(*old);
	*old = new_content;
	return (1);
}
