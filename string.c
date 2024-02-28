#include "shell.h"

/**
 * _strlen - will return the length of a string
 * @s: the string
 *
 * Return: ength of string
 */
int _strlen(char *s)
{
	int index = 0;

	if (!s)
		return (0);

	while (*s++)
		index++;
	return (index);
}

/**
 * _strcmp - performs comparison of two strangs kength,
 * @s1: str 1
 * @s2: str 2
 *
 * Return: negative if str 1 less than str 2,
 * positive if str 1 greator than str 2,
 * zero if str 1 equals str 2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * start_with - checks if needle starts with haystack
 * @haystack: string
 * @needle: the substrin
 *
 * Return: address of next char of haystack or NULL
 */
char *start_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings,
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
