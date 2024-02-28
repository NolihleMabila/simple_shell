#include "shell.h"

/**
 **_strncpy - function that copies a string,
 *@dest: destination
 *@src: tsource
 *@n: num of characters
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int index, k;
	char *str = dest;

	index = 0;
	while (src[index] != '\0' && index < n - 1)
	{
		dest[index] = src[index];
		index++;
	}
	if (index < n)
	{
		k = index;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (str);
}

/**
 **_strncat - function that concatenates two strings,
 *@dest: dest
 *@src: source string 1
 *@n: num
 * Return: str conactinates
 */
char *_strncat(char *dest, char *src, int n)
{
	int index, k;
	char *str = dest;

	index = 0;
	k = 0;
	while (dest[index] != '\0')
		index++;
	while (src[k] != '\0' && k < n)
	{
		dest[index] = src[k];
		index++;
		k++;
	}
	if (k < n)
		dest[index] = '\0';
	return (str);
}

/**
 **_strchr - will locates a char in a string,
 *@s: str
 *@c: char
 *Return: pointer if Sucess
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

