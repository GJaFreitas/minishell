/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:30:50 by gjacome-          #+#    #+#             */
/*   Updated: 2024/08/19 15:17:50 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*sub_str;

	slen = ft_strlen((char *)s);
	if (start > slen)
		return (ft_strdup(""));
	slen = ft_strlen((char *)s + start);
	if (len > slen)
		len = slen;
	sub_str = malloc(len + 1);
	if (sub_str == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = 0;
	return (sub_str);
}
