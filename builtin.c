#include "shell.h"

/**
 * _myexit - exits the shell,
 * @info: Structure info_t,
 *  Return: return an exit status
 *         (0) if arugument at index 0 == exit
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the directory
 * @info: Structure
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *str, *dir, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
	if (!str)
	{
		_puts("TODO: >>getcwd failure emsg here.<<\n");
	}

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
		{
			puts("Error: HOME not set\n");
		return (1);
		}
		chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts("Error: OLDPWD not set\n");
			return (1);
		}
		_puts(dir);
		_putchar('\n');
		chdir_ret = chdir(dir);
	}

	else
		chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1)
	{
		print_error(info, "cannot command to ");
		_eputs(info->argv[1]), _eputchar('\n');
		return (1);
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * _myhelp - prints help information
 * @info: Structure containing command information
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **args_array;

	args_array = info->argv;
	_puts("Help. Function not yet implemented \n");
	/**
	 * This condition is always false,
	 * so the code below it is never executed.
	 * I'm assuming you intended to print the first
	 * argument passed to the function.
	 * If so, you can remove this conditionIf not,
	 * you can modify it according to your intention.
	*/
	if (0)
		_puts(*args_array);
	return (0);
}

