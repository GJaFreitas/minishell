/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:43:30 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/07 17:43:31 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char *const argv[], t_env *env)
{
	t_env	*current;

	(void)argv;
	current = env;
	while (current)
	{
		if (current->exported && current->value[0] != '\0')
			ft_printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
