#include "memory.h"

t_garbage_col	*garbage_col(void)
{
	static t_garbage_col	g;

	return (&g);
}

void	*alloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	total;

	total = nmemb * size;
	if (total == 0)
		return (NULL);
	if (total / size != nmemb)
		return (NULL);
	ret = ft_calloc(nmemb, size);
	list_add(&garbage_col()->head, ret);
	garbage_col()->size++;
	return (ret);
}

void	free_this(void *ptr)
{
	if (!ptr)
		return ;
	list_remove(&garbage_col()->head, ptr);
	garbage_col()->size--;
	free(ptr);
}

void	assure_memory(void)
{
	list_free_all(&garbage_col()->head);
}
