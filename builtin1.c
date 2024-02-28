#include "shell.h"

/**
 * _myhistory - function displays the history list,
 * @info: Structure
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->hist);
	return (0);
}
/**
 * unset_alias - function that sets the alias of a string,
 * @info: Structure
 * @str: String
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *k, character;
	int ret;

	k = _strchr(str, '=');
	if (!k)
		return (1);
	character = *k;
	*k = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*k = character;
	return (ret);
}

/**
 * set_alias - function that sets an alias to string,
 * @info: structure,
 * @str: string,
 * Return: Always 0 on success, 1 on error
 */

int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints alias
 * @node: node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *ptr = NULL, *b = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (b = node->str; b <= ptr; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - my alias
 * @info: Structure
 * Return: Always 0
 */

int _myalias(info_t *info)
{
	int index = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		ptr = _strchr(info->argv[index], '=');
		if (ptr)
		{
			set_alias(info, info->argv[index]);
		}
		else
		{
			print_alias(node_starts_with(info->alias, info->argv[index], '='));
		}
	}
	return (0);
}
