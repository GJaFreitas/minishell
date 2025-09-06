/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:13:18 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/09/06 17:14:16 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_hdoc	*hdoc_norm(t_hdoc *ptr)
{
	static t_hdoc	*this;

	if (ptr)
		this = ptr;
	else
		return (this);
	return (NULL);
}
