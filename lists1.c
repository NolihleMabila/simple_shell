#include "shell.h"

/**
 * list_len - responsible for determining the length of linked list
 * @h: irst node
 *
 * Return: size of the linked list.
 */
size_t list_len(const list_t *h)
{
	size_t index = 0;

	while (h)
	{
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * list_to_strings - will return an argv  of strings of the list
 * @head: first node
 *
 * Return: the argv of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t index = list_len(head), k;
	char **strings;
	char *str;

	if (!head || !index)
		return (NULL);
	strings = malloc(sizeof(char *) * (index + 1));
	if (!strings)
		return (NULL);
	for (index = 0; node; node = node->next, index++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < index; k++)
				free(strings[k]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strings[index] = str;
	}
	strings[index] = NULL;
	return (strings);
}


/**
 * print_list - will prints all elements of thelinked list,
 * @h: first node
 *
 * Return: size of the linked list.
 */
size_t print_list(const list_t *h)
{
	size_t index = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: head node
 * @prefix: prefix
 * @c: the next character after the prefix,
 *
 * Return: node for a match, otherwise null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = start_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - function gets the index of a node,
 * @head: head node
 * @node: node
 *
 * Return: index of node otherwise -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
