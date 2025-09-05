	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:53:27 by gjacome-          #+#    #+#             */
/*   Updated: 2025/05/19 19:26:49 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static size_t	smallest(size_t n1, size_t n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

// Copies from the old ptr and then fills the rest of the memory with 0's
void	*ft_realloc(void *old, size_t prev_size, size_t new_size)
{
	void	*new;

	new = malloc(new_size);
	ft_memcpy(new, old, smallest(prev_size, new_size));
	if (new_size > prev_size)
		ft_bzero(new + prev_size, new_size - prev_size);
	free(old);
	return (new);
}
