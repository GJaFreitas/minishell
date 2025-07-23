/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:52:31 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/07/23 16:57:32 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	print_sorted_env(t_env *env_list)
{
    t_env	*current;
    t_env	**sorted;
    int		count;
    int		i;
    int		j;

    count = 0;
    current = env_list;
    while (current)
    {
        count++;
        current = current->next;
    }
    sorted = ft_calloc(count, sizeof(t_env *));
    if (!sorted)
        return ;
    current = env_list;
    i = 0;
    while (current)
    {
        sorted[i++] = current;
        current = current->next;
    }
    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - i - 1; j++)
        {
            if (env_var_cmp(sorted[j], sorted[j + 1]) > 0)
            {
                current = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = current;
            }
        }
    }
    for (i = 0; i < count; i++)
    {
        ft_printf("declare -x %s", sorted[i]->key);
        if (sorted[i]->value[0] != '\0')
            ft_printf("=\"%s\"", sorted[i]->value);
        ft_printf("\n");
    }
    
    free(sorted);
}
