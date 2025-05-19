/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:23:12 by gjacome-          #+#    #+#             */
/*   Updated: 2025/04/30 00:56:24 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <stdint.h>

static inline _Bool	is_aligned(const void *restrict pointer,
size_t byte_count)
{
	return ((uintptr_t)pointer % byte_count == 0);
}

static void	*__optimization(void *dest, const void *src,
size_t n, void *ret_ptr)
{
	size_t	increment;

	increment = sizeof(t_ul);
	while (!is_aligned(dest, n))
		*(t_uchar *)dest++ = *(t_uchar *)src++;
	n -= ret_ptr - dest;
	while (n >= increment)
	{
		*(t_ul *)dest = *(t_ul *)src;
		dest += increment;
		src += increment;
		n -= increment;
	}
	while (n > 0)
	{
		*(t_uchar *)dest++ = *(t_uchar *)src++;
		n--;
	}
	return (ret_ptr);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*ret_ptr;

	ret_ptr = dest;
	if (!dest || !src)
		return (NULL);
	if (n > 12)
		return (__optimization(dest, src, n, ret_ptr));
	while (n > 0)
	{
		*(char *)dest = *(char *)src;
		dest++;
		src++;
		n--;
	}
	return (ret_ptr);
}
