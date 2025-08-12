/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:42:31 by gjacome-          #+#    #+#             */
/*   Updated: 2025/08/12 18:12:24 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		strlen;

	strlen = ft_strlen((char *)s);
	new_str = malloc(strlen + 1);
	if (new_str == NULL)
		return (NULL);
	if (strlen == 0)
		new_str[0] = 0;
	else
		ft_strlcpy(new_str, s, strlen + 1);
	return (new_str);
}
