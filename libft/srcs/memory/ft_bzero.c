/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:19:37 by gjacome-          #+#    #+#             */
/*   Updated: 2025/04/30 00:56:46 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <stdint.h>

static inline _Bool	is_aligned(const void *restrict pointer,
size_t byte_count)
{
	return ((uintptr_t)pointer % byte_count == 0);
}

static void	__optimization(void *dest, size_t n)
{
	size_t	increment;

	increment = sizeof(t_ul);
	while (!is_aligned(dest, n))
	{
		*(t_uchar *)dest++ = (t_uchar)0;
		n--;
	}
	while (n >= increment)
	{
		*(t_ul *)dest = (t_ul)0;
		dest += increment;
		n -= increment;
	}
	while (n > 0)
	{
		*(t_uchar *)dest++ = (t_uchar)0;
		n--;
	}
}

void	ft_bzero(void *s, size_t n)
{
	if (n > 12)
		return (__optimization(s, n), (void)0);
	while (n)
	{
		*(t_uchar *)s = (t_uchar)0;
		s++;
		n--;
	}
}
