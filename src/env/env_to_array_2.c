/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:21:07 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/06 19:21:48 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__matar_o_env(t_env *env)
{
	t_env	*cur;
	t_env	*prev;

	cur = env;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev);
	}
}

t_env	*array_to_env(char **env)
{
	t_env	*list_env;
	t_env	*cur;

	cur = list_env;
	cur = create_env_node(*env);
	env++;
	while (*env)
	{
		cur->next = create_env_node(*env);
		if (cur->next == NULL)
			__matar_o_env(list_env);
		env++;
		cur = list_env->next;
	}
	return (list_env);
}
