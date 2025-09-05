/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:42:55 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 18:43:30 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*norm(t_cmd *cmd)
{
	static t_cmd	*this;

	if (!this)
		this = cmd;
	if (cmd == NULL)
		return (this);
	return (NULL);
}
