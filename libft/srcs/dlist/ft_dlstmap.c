/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:25:06 by gjacome-          #+#    #+#             */
/*   Updated: 2025/04/29 10:29:49 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_dlist	*ft_dlistmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*new_lst;

	new_lst = ft_dlistnew((*f)(lst->content));
	if (new_lst == NULL)
	{
		(*del)(new_lst->content);
		return (NULL);
	}
	while (lst->next != NULL)
	{
		lst = lst->next;
		ft_dlistadd_back(&new_lst, ft_dlistnew((*f)(lst->content)));
	}
	return (new_lst);
}
