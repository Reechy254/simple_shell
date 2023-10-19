#include "shell.h"

/**
 * list_len - gets th length of a linked list
 * @firstnode_ptr: the  pointer to the first node
 *
 * Return: the size of the list
 */

size_t list_len(const list_t *firstnode_ptr)
{
	size_t b = 0;

	while (firstnode_ptr)
	{
		firstnode_ptr = firstnode_ptr->next;
		b++;
	}
	return (b);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(strlen_(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = cp_strg(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - outputs all elements of a list_t linked list
 * @firstnode_ptr: the  pointer to the first node
 *
 * Return: size of list
 */

size_t print_list(const list_t *firstnode_ptr)
{
	size_t b = 0;

	while (firstnode_ptr)
	{
		_puts(con_num(firstnode_ptr->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(firstnode_ptr->str ? firstnode_ptr->str : "(nil)");
		_puts("\n");

	firstnode_ptr = firstnode_ptr->next;
		b++;

	}
	return (b);
}

/**
 * prefix_node - returns node whose string starts with prefix
 * @node_pointer: pointer to lists head node
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */

list_t *prefix_node(list_t *node_pointer, char *prefix, char c)
{
	char *a = NULL;

	while (node_pointer)
	{
		a = starts_with(node_pointer->str, prefix);
		if (a && ((c == -1) || (*a == c)))
			return (node_pointer);
		node_pointer = node_pointer->next;
	}
	return (NULL);
}

/**
 * get_nodeindex - gets the index of a node
 * @head: the  pointer to the list head
 * @node_pointer: the pointer to the node
 *
 * Return: the node index  or -1
 */

ssize_t get_nodeindex(list_t *head, list_t *node_pointer)
{
	size_t b = 0;

	while (head)
	{
		if (head == node_pointer)
			return (b);
		head = head->next;
		b++;
	}
	return (-1);
}

