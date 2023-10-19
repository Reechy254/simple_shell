#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @firstnode_ptr: address of pointer to head node
 * @str: the string field of a node
 * @histo_nodeindex: node index used by history
 *
 * Return: size of list
 */

list_t *add_node(list_t **firstnode_ptr, const char *str, int histo_nodeindex)
{
	list_t *new_firstnode_ptr;

	if (!firstnode_ptr)
		return (NULL);
	new_firstnode_ptr = malloc(sizeof(list_t));
	if (!new_firstnode_ptr)
		return (NULL);
	mem_fill((void *)new_firstnode_ptr, 0, sizeof(list_t));
	new_firstnode_ptr->histo_nodeindex = histo_nodeindex;
	if (str)
	{
		new_firstnode_ptr->str = strdup_(str);
		if (!new_firstnode_ptr->str)
		{
			free(new_firstnode_ptr);
			return (NULL);
		}
	}
	new_firstnode_ptr->next = *firstnode_ptr;
	*firstnode_ptr = new_firstnode_ptr;
	return (new_firstnode_ptr);
}

/**
 * add_node_end - adds a node to the end of the list
 * @firstnode_ptr: address to the  pointer of the head node
 * @str: the strings field of node
 * @histo_nodeindex: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **firstnode_ptr, const char *str,
int histo_nodeindex)

{
	list_t *new_node, *node;

	if (!firstnode_ptr)
		return (NULL);

	node = *firstnode_ptr;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	mem_fill((void *)new_node, 0, sizeof(list_t));
	new_node->histo_nodeindex = histo_nodeindex;
	if (str)
	{
		new_node->str = strdup_(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*firstnode_ptr = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: the  pointer to the  first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * del_indexnode - deletes node at any given index
 * @firstnode_ptr: address to a pointer of the first node
 * @index: index of the node to be deleted
 *
 * Return: 1 on success, 0 on failure
 */
int del_indexnode(list_t **firstnode_ptr, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!firstnode_ptr || !*firstnode_ptr)
		return (0);

	if (!index)
	{
		node = *firstnode_ptr;
		*firstnode_ptr = (*firstnode_ptr)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *firstnode_ptr;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_listnodes - free all the lists nodes
 * @headnode_ptr: address to a  pointer to head node
 *
 * Return: void
 */

void free_listnodes(list_t **headnode_ptr)
{
	list_t *node, *next_node, *firstnode_ptr;

	if (!headnode_ptr || !*headnode_ptr)
		return;
	firstnode_ptr = *headnode_ptr;
	node = firstnode_ptr;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*headnode_ptr = NULL;
}

