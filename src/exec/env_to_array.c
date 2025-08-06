/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:38:37 by gvon-ah-          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
# include "minishell.h"

static int count_envs(t_env *input)
{
	int i;
	t_env *current;

	i = 0;
	current = input;
	while (current)
    {
        i++;
        current = current->next;
    }
	return (i);
}

static int count_envs_pointers(char **input)
{
	int i;
	char **current;

	i = 0;
	current = input;
	while (current[i])
		i++;
	return (i);
}

char **env_to_array(t_env *env)
{
    int count;
    t_env *current;
    char **env_array;
    int i;

	i = 0;
	count = count_envs(env);
    env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array)
        return (NULL);
    current = env;
    while (current)
    {
        env_array[i] = ft_strjoin(ft_strjoin(current->key, "="), current->value);
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

static t_env	*create_env_node(char *str)
{
	t_env	*new_node;
	int	i;

	i = 0;
	new_node = malloc(sizeof(s_env));
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
