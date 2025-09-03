/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:22 by bag               #+#    #+#             */
/*   Updated: 2025/09/03 19:48:44 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
 * Functionality:
 * 	Initialize
 * 	Free
*/

static char	*__extract_to_from(char *str, char end, char start);

static inline void	__increment_shlvl(t_env *env, char cwd[CWD_BUFFER])
{
	int	idx;
	int	n;

	ft_bzero(cwd, CWD_BUFFER);
	idx = env_var_exists(env, "SHLVL");
	if (idx != -1)
	{
		ft_strlcpy(cwd, env_get_value_index(env, idx), CWD_BUFFER);
		n = ft_atoi(cwd);
		n++;
		ft_bzero(cwd, 12);
		ft_itoa_buf(n, cwd, CWD_BUFFER);
		env_change_val(env, idx, cwd);
	}
	else
	{
		ft_strlcpy(cwd, "SHLVL=1", 9);
		env_add(env, cwd);
	}
}

void	start_env_vars(t_env *env)
{
	char	cwd[CWD_BUFFER];

	ft_bzero(cwd, CWD_BUFFER);
	getcwd(cwd, CWD_BUFFER);
	env_add_key_value_pair(env, "PWD", cwd);
	env_add_key_value_pair(env, "OLD_PWD", cwd);
	__increment_shlvl(env, cwd);
}

t_env	*init_env(char **old)
{
	t_env	*env;
	unsigned int	i;

	env = ft_calloc(1, sizeof(t_env));
	env->size = ENV_INIT_SIZE;
	env->keys = malloc(ENV_INIT_SIZE * sizeof(char *));
	env->values = malloc(ENV_INIT_SIZE * sizeof(char *));
	i = 0;
	while (*old)
	{
		env->keys[i] = __extract_to_from(*old, '=', -1);
		env->values[i] = __extract_to_from(*old, '\0', '=');
		old++;
		i++;
		if (i > env->size)
			env_grow(env);
	}
	env->used = i;
	start_env_vars(env);
	return (env);
}

/*
 * start == -1 -> Desde o inicio
*/
static char	*__extract_to_from(char *str, char end, char start)
{
	int	i;

	i = 0;
	while (start != -1 && str[i++] != start);
	str += i;
	while (str[i] && str[i] != end)
		i++;
	return (ft_substr(str, 0, i));
}
