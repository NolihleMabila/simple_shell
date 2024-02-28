#include "shell.h"

/**
 *_putsfd - prints an input string,
 * @str: string input,
 * @f: file to write on to
 * Return: the number of chars read and printed.
 */
int _putsfd(char *str, int f)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += _putfd(*str++, f);
	}
	return (index);
}

/**
 * _putfd - writes characters to a file
 * @c: char
 * @f: file
 *
 * Return: On success 1, On error, -1 is returned,
 * and errno is set appropriately.
 */
int _putfd(char c, int f)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(f, buffer, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * _eputchar - responsible for writing a character.
 * @c: char.
 * Return: On success 1,
 * On error -1 is returned, and errno is set appropriately,
 */
int _eputchar(char c)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, index);
		index= 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 *_eputs - prints a string,
 * @str: string
 *
 * Return: None.
 */
void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}
