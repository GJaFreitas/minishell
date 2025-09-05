/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:22 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 16:34:08 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__create_sorted_array(int *arr, char **keys, int size, int *used);
static int	*env_create_sorted(t_env *env);

void	env_print_sorted(t_env *env)
{
	static char		declare[12] = "declare -x ";
	unsigned int	i;

	i = 0;
	env->sorted = env_create_sorted(env);
	while (i < env->used)
	{
		ft_printf("%s", declare);
		ft_printf("%s", env->keys[env->sorted[i]]);
		if (env->values[env->sorted[i]])
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			if (env->values[env->sorted[i]][0])
				ft_printf("%s", env->values[env->sorted[i]]);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

static int	*env_create_sorted(t_env *env)
{
	int	*arr;
	int	*temp;

	if (env->sorted && is_env_clean(env, ENV_SORTING))
		return (env->sorted);
	else if (env->sorted)
		free(env->sorted);
	arr = malloc(sizeof(int) * env->used);
	temp = ft_calloc((env->used + 1), sizeof(int));
	__create_sorted_array(arr, env->keys, env->used, temp);
	free(temp);
	env->dirty = clean_env(env, ENV_SORTING);
	return (arr);
}

static void	__create_sorted_array(int *arr, char **keys, int size, int *used)
{
	int	i;
	int	j;
	int	cur;

	j = 0;
	while (j < size)
	{
		cur = 0;
		while (cur < size && used[cur])
			cur++;
		i = 0;
		while (i < size)
		{
			while (i < size && used[i])
				i++;
			if (i < size && cur < size && ft_strcmp(keys[i], keys[cur]) < 0)
				cur = i;
			i++;
		}
		arr[j] = cur;
		used[cur] = 1;
		j++;
	}
}
