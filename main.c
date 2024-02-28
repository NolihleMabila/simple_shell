#include "shell.h"

/**
 * main - the entry point.
 * @ac: argument count,
 * @av: arg vector. arrays
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int file = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file)
		: "r" (file));

	if (ac == 2)
	{
		file = open(av[1], O_RDONLY);
		if (file == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = file;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
