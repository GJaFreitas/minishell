/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:30:08 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/06 19:30:10 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_var(t_env *env, char *var)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (!ft_strcmp(var, cur->key))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
