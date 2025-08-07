/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:53:48 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/07 18:11:50 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	__count_args(char *const argv[])
{
	int	i;

	i = 0;
	while (argv[i++]);
	return (i);
}

int	ft_export(char *const argv[], t_env *env)
{
	if (__count_args(argv) > 0)
		env_add(env, *argv);
	else
		env_print_sorted(env);
	exit(0);
}
