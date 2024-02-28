#include "shell.h"

/**
 * bfree - reponsible for freeing a pointer the NULLS its address
 * @ptr: pointer
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
