/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:01:57 by gjacome-          #+#    #+#             */
/*   Updated: 2024/08/19 15:17:40 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strrchr(const char *s, int ch)
{
	char			*return_ptr;
	unsigned char	c;

	c = (unsigned char)ch;
	return_ptr = NULL;
	while (*s)
	{
		if (*s == c)
			return_ptr = (char *)s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (return_ptr);
}
