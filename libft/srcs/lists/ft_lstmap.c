/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:25:06 by gjacome-          #+#    #+#             */
/*   Updated: 2024/08/19 15:14:50 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;

	new_lst = ft_lstnew((*f)(lst->content));
	if (new_lst == NULL)
	{
		(*del)(new_lst->content);
		return (NULL);
	}
	while (lst->next != NULL)
	{
		lst = lst->next;
		ft_lstadd_back(&new_lst, ft_lstnew((*f)(lst->content)));
	}
	return (new_lst);
}
