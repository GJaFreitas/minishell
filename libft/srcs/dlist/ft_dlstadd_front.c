/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:21:56 by gjacome-          #+#    #+#             */
/*   Updated: 2025/04/29 10:26:49 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_dlistadd_front(t_dlist **head, t_dlist *node)
{
	t_dlist	*temp;

	temp = *head;
	if (!head || !node)
		return ;
	node->next = *head;
	*head = node;
	temp->prev = node;
}
