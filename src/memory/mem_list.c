#include "memory.h"

static t_node	*new_node(void *content)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = content;
	return (node);
}

void	list_add(t_node **head, void *content)
{
	t_node	*current;

	if (!head || !content)
		return ;
	if (!*head)
	{
		*head = new_node(content);
	}
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node(content);
		current->next->prev = current;
	}
}

void	list_remove(t_node **head, void *ptr)
{
	t_node	*current;

	if (!head || !ptr)
		return ;
	current = *head;
	while (current)
	{
		if (current->content == ptr)
		{
			if (current->prev)
				current->prev->next = current->next;
			else
				*head = current->next;
			if (current->next)
				current->next->prev = current->prev;
			free(current);
			return ;
		}
		current = current->next;
	}
}

void	list_free_all(t_node **head)
{
	t_node	*current;
	t_node	*next;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*head = NULL;
}
