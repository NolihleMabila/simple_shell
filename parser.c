#include "shell.h"

/**
 * is_cmd -  function determines if a file is an executable command,
 * @info: the info structure,
 * @path: path
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
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
 * dup_chars - function duplicates characters.
 * @pathstr: path string
 * @start: the starting index,
 * @stop: stop index.
 *
 * Return: will return the pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int index = 0, j = 0;

	for (j = 0, index = start; index < stop; index++)
		if (pathstr[index] != ':')
			buf[j++] = pathstr[index];
	buf[j] = 0;
	return (buf);
}

/**
 * fnd_path -  function searches for a command in the PATH string
 * @info: the info structure
 * @pathstr: PATH string
 * @cmd: command
 *
 * Return: the full path of  the command if found other iotherwise NULL
 */
char *fnd_path(info_t *info, char *pathstr, char *cmd)
{
	int index = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && start_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[index] || pathstr[index] == ':')
		{
			path = dup_chars(pathstr, curr_pos, index);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[index])
				break;
			curr_pos = index;
		}
		index++;
	}
	return (NULL);
}

