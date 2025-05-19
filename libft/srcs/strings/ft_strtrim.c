/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:50:02 by gjacome-          #+#    #+#             */
/*   Updated: 2024/08/19 15:17:45 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;

	if (!s1 || !set)
		return (NULL);
	if (ft_strchr(set, *s1))
		while (*s1 && ft_strchr(set, *s1))
			s1++;
	i = ft_strlen((char *)s1);
	if (ft_strchr(set, s1[i]))
		while (ft_strchr(set, s1[i]))
			i--;
	return (ft_substr(s1, 0, i + 1));
}
