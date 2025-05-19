/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:40:55 by gjacome-          #+#    #+#             */
/*   Updated: 2024/08/19 15:16:33 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstsize;
	size_t	i;

	i = 0;
	dstsize = ft_strlen(dst);
	if (dstsize >= size)
		return (size + ft_strlen((char *)src));
	while (src[i] && dstsize < size - 1)
	{
		dst[dstsize] = src[i];
		dstsize++;
		i++;
	}
	dst[dstsize] = 0;
	return (ft_strlen((char *)dst) + ft_strlen((char *)&src[i]));
}
