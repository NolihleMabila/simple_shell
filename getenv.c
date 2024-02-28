#include "shell.h"

/**
 * get_environ - returns copy of an environment.
 * @info: Structure
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - responsible to removing a environment
 * @info: Structure
 * @var: variable
 * Return: environ
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t index = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = start_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a enviro virable,
 * @info: Structur
 * @var: var
 * @value: value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *pointer;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		pointer = start_with(node->str, var);
		if (pointer && *pointer == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
