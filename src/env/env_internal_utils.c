/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_internal_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:22 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 18:43:30 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_grow(t_env *env)
{
	env->values = ft_realloc(env->values, env->size * sizeof(char *), env->size
			* 2 * sizeof(char *));
	env->keys = ft_realloc(env->keys, env->size * sizeof(char *), env->size * 2
			* sizeof(char *));
	env->size *= 2;
}

void	free_env(t_env *env)
{
	uint32_t	i;

	i = 0;
	while (i < env->used)
	{
		free(env->keys[i]);
		free(env->values[i]);
		i++;
	}
	free(env->keys);
	free(env->values);
	if (env->sorted)
		free(env->sorted);
	if (env->array)
		free_env_array(env->array);
	free(env);
}

inline int	is_env_clean(t_env *env, int flag)
{
	if (flag == ENV_ARRAYING)
	{
		if (env->dirty == ENV_A || env->dirty == ENV_CLEAN)
			return (1);
	}
	else if (flag == ENV_SORTING)
	{
		if (env->dirty == ENV_S || env->dirty == ENV_CLEAN)
			return (1);
	}
	return (0);
}

inline enum e_env_dirt	clean_env(t_env *env, int flag)
{
	if (flag == ENV_ARRAYING)
	{
		if (env->dirty == ENV_S)
			return (ENV_CLEAN);
		else
			return (ENV_A);
	}
	else if (flag == ENV_SORTING)
	{
		if (env->dirty == ENV_A)
			return (ENV_CLEAN);
		else
			return (ENV_S);
	}
	return (0);
}
