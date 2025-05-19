/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:22:55 by gjacome-          #+#    #+#             */
/*   Updated: 2024/08/19 15:17:26 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret_str;
	int		i;

	i = 0;
	if (s[0] == 0)
		return (ft_strdup(""));
	ret_str = ft_calloc(ft_strlen((char *)s) + 1, sizeof(char));
	if (!ret_str)
		return (NULL);
	while (s[i])
	{
		ret_str[i] = (*f)(i, s[i]);
		i++;
	}
	ret_str[i] = 0;
	return (ret_str);
}
