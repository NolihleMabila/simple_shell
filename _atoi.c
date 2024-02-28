#include "shell.h"

/**
 *_isalpha -  funsction that check for checks for alphabetics,
 *@c: char
 *Return: 1 if char is alphabetic, 0 otherwise,
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - responsible for converting a string into an integer,
 *@string: string to convert
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *string)
{
	int index, sign = 1, flag = 0, outpt;
	unsigned int reslt = 0;

	for (index = 0;  string
	[index] != '\0' && flag != 2; index++)
	{
		if (string[index] == '-')
			sign *= -1;

		if (string[index] >= '0' && string[index] <= '9')
		{
			flag = 1;
			reslt *= 10;
			reslt += (string[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		outpt = -reslt;
	else
		outpt = reslt;

	return (outpt);
}

/**
 * is_delim - checks for a delimeter
 * @c: char to check for the specified delimeter
 * @delim: delimeter to check,
 * Return: 1 if true, 0 if false.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * interactive - check shell's mode will return true if interactive
 * @info: struct
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

