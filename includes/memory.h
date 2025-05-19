#ifndef MEMORY_H
# define MEMORY_H

# include <stdlib.h>
# include "libft.h"

typedef struct s_node
{
	void		*content;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_garbage_col
{
	t_node	*head;
	size_t	size;
}	t_garbage_col;

/**********************

Returns pointer to memory block of
'size' * 'nmemb' bytes;
If 'size' * 'nmemb' is 0 returns NULL;

***********************/
void	*alloc(size_t nmemb, size_t size);


/**********************

Removes the node with 'ptr' from the
list and frees the pointer 'ptr';

***********************/
void	free_this(void *ptr);


/**********************

Frees all unfreed memory if any;

***********************/
void	assure_memory(void);



/**********************

Adds a node with content to the list
pointed to by 'head';
If 'head' or 'content' dont
exist returns NULL;

***********************/
void	list_add(t_node **head, void *content);

/**********************

Removes the node with 'ptr' from the
list;

***********************/
void	list_remove(t_node **head, void *ptr);

/**********************

Frees all nodes in the list
and sets the head to NULL;
If 'head' is NULL
does nothing;

***********************/
void	list_free_all(t_node **head);

void	test_garbage_col(void);
#endif
