/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:18:43 by gjacome-          #+#    #+#             */
/*   Updated: 2025/04/29 10:30:35 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_dlist	*ft_dlistnew(void *content)
{
	t_dlist	*newnode;

	newnode = ft_calloc(1, sizeof(t_dlist));
	if (newnode == NULL)
		return (NULL);
	newnode->content = content;
	return (newnode);
}
