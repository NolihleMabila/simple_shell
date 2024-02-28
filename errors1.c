#include "shell.h"

/**
 * _erratoi - function that converts a string to an integer,
 * @s: string
 * Return: 0 for Success, else -1
 */
int _erratoi(char *s)
{
	int index = 0;
	unsigned long int reslt = 0;

	if (*s == '+')
		s++;
	for (index = 0;  s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			reslt *= 10;
			reslt += (s[index] - '0');
			if (reslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (reslt);
}
/**
 * print_d - funtion to print a describer
 * @input: input
 * @d: filename
 *
 * Return: number of characters printed
 */
int print_d(int input, int d)
{
	int (*__putchar)(char) = _putchar;
	int index, c = 0;
	unsigned int _abs_, currnt;

	if (d == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		c++;
	}
	else
		_abs_ = input;
	currnt = _abs_;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (_abs_ / index)
		{
			__putchar('0' + currnt / index);
			c++;
		}
		currnt %= index;
	}
	__putchar('0' + currnt);
	c++;

	return (c);
}
/**
 * convert_number - clone for atoi
 * @num: number,
 * @base: base,
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arry;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long a = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		a = -num;
		sign = '-';

	}
	arry = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do	{
		*--pointer = arry[a % base];
		a /= base;
	} while (a != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}
/**
 * print_error - function that prints the error message
 * @info: struct
 * @estr: error type
 * Return: 0 Success, else
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
/**
 * remove_comments - function function is to replace the # char
 * @buf: buffer
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
}
