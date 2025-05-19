/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:36:26 by gjacome-          #+#    #+#             */
/*   Updated: 2024/08/19 15:16:26 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_len;
	char	*new_str;

	total_len = (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	new_str = malloc(total_len);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s1, total_len);
	ft_strlcat(new_str, s2, total_len);
	return (new_str);
}
