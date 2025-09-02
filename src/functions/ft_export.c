/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:53:48 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/09/01 16:06:39 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_export(char *const argv[], t_env *env)
{
	int	i;
	int	retval;

	i = 0;
	retval = 0;
	if (count_args(argv) > 1)
	{
		while (argv[i + 1])
		{
			if (argv[i + 1][0])
				retval = env_add(env, argv[i + 1]);
			i++;
		}
	}
	else
		env_print_sorted(env);
	return (retval);
}
