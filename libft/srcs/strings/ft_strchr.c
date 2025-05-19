/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:59:38 by gjacome-          #+#    #+#             */
/*   Updated: 2024/08/19 15:16:08 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../libft.h"

char	*ft_strchr(const char *s, int ch)
{
	char			*ret_ptr;
	unsigned char	c;

	c = (unsigned char)ch;
	ret_ptr = NULL;
	while (*s && *s != c)
		s++;
	if (*s == c)
		ret_ptr = (char *)s;
	if (c == 0)
		return ((char *)s);
	return (ret_ptr);
}
