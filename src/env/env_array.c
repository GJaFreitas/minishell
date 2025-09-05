/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:22 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 16:34:07 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*__strjoin_mod(char *s1, char *s2);

char	**env_to_array(t_env *env)
{
	char			**arr;
	unsigned int	i;
	unsigned int	j;

	if (env->array && is_env_clean(env, ENV_ARRAYING))
		return (env->array);
	else if (env->array)
		free_env_array(env->array);
	arr = malloc(sizeof(char *) * (env->used + 1));
	(i = 0, j = 0);
	while (j < env->used)
	{
		if (env->values[j])
		{
			arr[i] = __strjoin_mod(env->keys[j], env->values[j]);
			i++;
		}
		j++;
	}
	arr[i] = NULL;
	env->dirty = clean_env(env, ENV_ARRAYING);
	env->array = arr;
	return (arr);
}

void	free_env_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

// +1 -> '='  +1 -> '\0'
static char	*__strjoin_mod(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(1, ft_strlen(s1) + ft_strlen(s2) + 1 + 1);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = i;
	new[j++] = '=';
	i = -1;
	while (s2[++i])
		new[j++] = s2[i];
	return (new);
}
