#include "shell.h"

/**
 * input_buf - checks for buffers chained commands,
 * @info: struct
 * @buf: buffer
 * @len: length
 *
 * Return: bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t read = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		read = getline(buf, &len_p, stdin);
#else
		read = _getline(info, buf, &len_p);
#endif
		if (read > 0)
		{
			if ((*buf)[read - 1] == '\n')
			{
				(*buf)[read - 1] = '\0';
				read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = read;
				info->cmd_buf = buf;
			}
		}
	}
	return (read);
}

/**
 * get_input - reads the inout STIND
 * @info: truct
 *
 * Return: bytes
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t index, k, len;
	ssize_t read = 0;
	char **buf_p = &(info->arg), *pointer;

	_putchar(BUFFER_FLUSH);
	read = input_buf(info, &buf, &len);
	if (read == -1)
		return (-1);
	if (len)
	{
		k = index;
		pointer = buf + index;

		check_chain(info, buf, &k, index, len);
		while (k < len)
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}

		index = k + 1;
		if (index >= len)
		{
			index = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = pointer;
		return (_strlen(pointer));
	}

	*buf_p = buf;
	return (read);
}

/**
 * read_buf - frunction reads a buffer,
 * @info: struct,
 * @buf: buffer,
 * @i: size,
 *
 * Return: read text
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t rrad = 0;

	if (*i)
		return (0);
	rrad = read(info->readfd, buf, READ_BUFFER_SIZE);
	if (rrad >= 0)
		*i = rrad;
	return (rrad);
}

/**
 * _getline - reads the next line of input from STDIN
 * @info: struct,
 * @ptr: pointer to buffer, preallocated or NULL
 * @length: length
 *
 * Return: string read
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t index, len;
	size_t mn;
	ssize_t input = 0, num = 0;
	char *pointer = NULL, *new_p = NULL, *c;

	pointer = *ptr;
	if (pointer && length)
		num = *length;
	if (index == len)
		index = len = 0;

	input = read_buf(info, buffer, &len);
	if (input == -1 || (input == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + index, '\n');
	mn = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(pointer, num, num ? num + mn : mn + 1);
	if (!new_p)
		return (pointer ? free(pointer), -1 : -1);

	if (num)
		_strncat(new_p, buffer + index, mn - index);
	else
		_strncpy(new_p, buffer + index, mn - index + 1);

	num += mn - index;
	index = mn;
	pointer = new_p;

	if (length)
		*length = num;
	*ptr = pointer;
	return (num);
}

/**
 * sigintHandler - responsible for blocks ctrl-C,
 * @sig_num: signal num,
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
