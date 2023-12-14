#include "shell.h"

/**
 * _addnode - Adds a node to the start of a linked list.
 * @head: Address of pointer to the head node.
 * @str: String field of the new node.
 * @num: Node index used by history.
 *
 * Return: Address of the new head of the list.
 */
list_t *_addnode(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	mem_set((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * _addnode_end - Adds a node to the end of a linked list.
 * @head: Address of pointer to the head node.
 * @str: String field of the new node.
 * @num: Node index used by history.
 *
 * Return: Address of the new node at the end of the list.
 */
list_t *_addnode_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	mem_set((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
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
		*head = new_node;
	return (new_node);
}

/**
 * list_str - Prints only the str element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t list_str(const list_t *h)
{
	size_t m = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		m++;
	}
	return (m);
}

/**
 * delete_node_at_index - Deletes a node at a given index.
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int m = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (m == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		m++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * _listfree - Frees all nodes of a linked list.
 * @head_ptr: Address of pointer to the head node.
 *
 * Return: Void.
 */
void _listfree(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
