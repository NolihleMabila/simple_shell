#include "shell.h"

/**
 * **strtow - splits a string into words using a delimiter
 * @str: input string
 * @d: delimeter
 * Return: a pointer toi an array of strings, or NULL on failure.
 */

char **strtow(char *str, char *d)
{
	int index, l, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (index = 0; str[index] != '\0'; index++)
		if (!is_delim(str[index], d) && (is_delim(str[index + 1], d)
					|| !str[index + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (index = 0, l = 0; l < num_words; l++)
	{
		while (is_delim(str[index], d))
			index++;
		k = 0;
		while (!is_delim(str[index + k], d) && str[index + k])
			k++;
		s[l] = malloc((k + 1) * sizeof(char));
		if (!s[l])
		{
			for (k = 0; k < l; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[l][m] = str[index++];
		s[l][m] = 0;
	}
	s[l] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into multiple words.
 * @str: string
 * @d: delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int index, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (index = 0; str[index] != '\0'; index++)
		if ((str[index] != d && str[index + 1] == d) ||
		    (str[index] != d && !str[index + 1]) || str[index + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (index = 0, j = 0; j < num_words; j++)
	{
		while (str[index] == d && str[index] != d)
			index++;
		k = 0;
		while (str[index + k] != d && str[index + k] && str[index + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[index++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
