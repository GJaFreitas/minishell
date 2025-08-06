/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:40:08 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/06 18:13:13 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env *env_list)
{
    t_env	*current;
    t_env	*next;

    current = env_list;
    while (current)
    {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
}

t_env	*new_env_var(char *key, char *value, bool exported)
{
    t_env	*new;

    new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->exported = exported;
    new->next = NULL;
    return (new);
}

void	add_env_var(t_env **env_list, char *key, char *value, bool exported)
{
    t_env	*current;

    if (!env_list)
        return ;
    current = *env_list;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            if (exported)
                current->exported = true;
            return ;
        }
        current = current->next;
    }
    if (!*env_list)
        *env_list = new_env_var(key, value, exported);
    else
    {
        current = *env_list;
        while (current->next)
            current = current->next;
        current->next = new_env_var(key, value, exported);
    }
}

int	ft_env(char *const argv[], t_env *env);
{
    t_env	*current;

    current = env;
    while (current)
    {
        if (current->exported && current->value[0] != '\0')
            ft_printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    return (0);
}

int	env_var_cmp(t_env *a, t_env *b)
{
    return (ft_strcmp(a->key, b->key));
}
