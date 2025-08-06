/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:30:52 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/06 19:42:43 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **env)
{
	t_env	*env_list;
	int		i;
	char	*equals;
	char	*key;
	char	*value;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		equals = ft_strchr(env[i], '=');
		if (equals)
		{
			key = ft_substr(env[i], 0, equals - env[i]);
			value = ft_strdup(equals + 1);
			add_env_var(&env_list, key, value, 1);
			free(key);
			free(value);
		}
		i++;
	}
	return (env_list);
}

char	**env_list_to_array(t_env *env_list)
{
	int		count;
	t_env	*current;
	char	**env_array;
	char	*temp;

	current = env_list;
	count = 0;
	while (current)
	{
		if (current->exported)
			count++;
		current = current->next;
	}
	env_array = ft_calloc(count + 1, sizeof(char *));
	current = env_list;
	count = 0;
	while (current)
	{
		if (current->exported)
		{
			temp = ft_strjoin(current->key, "=");
			env_array[count] = ft_strjoin(temp, current->value);
			free(temp);
			count++;
		}
		current = current->next;
	}
	return (env_array);
}

int	ft_export_l(char * const*args, t_env **env_list)
{
	int		i;
	t_env	*var;
	char	*equals;

	i = 0;
	if (!args[i])
		return (print_sorted_env(*env_list), 0);
	while (args[++i])
	{
		equals = ft_strchr(args[i], '=');
		if (equals)
		{
			*equals = '\0';
			add_env_var(env_list, args[i], equals + 1, 1);
			*equals = '=';
		}
		else
		{
			var = find_env_var(*env_list, args[i]);
			if (var)
				var->exported = 1;
			else
				add_env_var(env_list, args[i], "", 1);
		}
	}
	return (0);
}
