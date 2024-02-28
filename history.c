#include "shell.h"

/**
 * get_history_file - returns the history file
 * @info: ruct
 *
 * Return: beffer
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
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
 * write_history - writes on a file
 * @info: struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t f;
	char *filenam = get_history_file(info);
	list_t *node = NULL;

	if (!filenam)
		return (-1);

	f = open(filenam, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenam);
	if (f == -1)
		return (-1);
	for (node = info->hist; node; node = node->next)
	{
		_putsfd(node->str, f);
		_putfd('\n', f);
	}
	_putfd(BUFFER_FLUSH, f);
	close(f);
	return (1);
}

/**
 * read_history - reads history from a file,
 * @info:struct
 *
 * Return: history on success, 0 otherwise.
 */
int read_history(info_t *info)
{
	int index, last = 0, line_count = 0;
	ssize_t f, rdlen, fsze = 0;
	struct stat st;
	char *buf = NULL, *filenam = get_history_file(info);

	if (!filenam)
		return (0);

	f = open(filenam, O_RDONLY);
	free(filenam);
	if (f == -1)
		return (0);
	if (!fstat(f, &st))
		fsze = st.st_size;
	if (fsze < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsze + 1));
	if (!buf)
		return (0);
	rdlen = read(f, buf, fsze);
	buf[fsze] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(f);
	for (index = 0; index < fsze; index++)
		if (buf[index] == '\n')
		{
			buf[index] = 0;
			build_history_list(info, buf + last, line_count++);
			last = index + 1;
		}
	if (last != index)
		build_history_list(info, buf + last, line_count++);
	free(buf);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->hist), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - appends linked ists
 * @info: Structure,
 * @buf: buffer
 * @linecount: linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->hist)
		node = info->hist;
	add_node_end(&node, buf, linecount);
	if (!info->hist)
		info->hist = node;
	return (0);
}

/**
 * renumber_history - renumbers the history,
 * @info: Structure
 * Return: the new history count.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->hist;
	int index = 0;

	while (node)
	{
		node->num = index++;
		node = node->next;
	}
	return (info->histcount = index);
}

