/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:38:37 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/06 19:39:50 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_envs(t_env *input)
{
	int		i;
	t_env	*current;

	i = 0;
	current = input;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**env_array;
	int		i;

	i = 0;
	env_array = malloc(sizeof(char *) * (count_envs(env) + 1));
	if (!env_array)
		return (NULL);
	current = env;
	while (current)
	{
		env_array[i] = ft_strjoin(ft_strjoin(current->key, "="),
				current->value);
		if (!env_array[i])
		{
			while (i > 0)
				free(env_array[--i]);
			return (free(env_array), NULL);
		}
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	free_env_array(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}


