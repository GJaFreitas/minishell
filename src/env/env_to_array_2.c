/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:21:07 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/06 19:40:47 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_env_node(char *str)
{
	t_env	*new_node;
	int		i;

	i = 0;
	new_node = malloc(sizeof(t_env));
	while (str[i] && str[i] != '=')
		i++;
	new_node->key = ft_substr(str, 0, i);
	str = str + i;
	new_node->value = ft_substr(str, 0, ft_strlen(str));
	new_node->next = NULL;
	return (new_node);
}

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

	cur = create_env_node(*env);
	list_env = cur;
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
