/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:18:43 by gjacome-          #+#    #+#             */
/*   Updated: 2025/04/29 10:31:10 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = ft_calloc(1, sizeof(t_list));
	if (newnode == NULL)
		return (NULL);
	newnode->content = content;
	return (newnode);
}
