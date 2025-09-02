/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:22 by bag               #+#    #+#             */
/*   Updated: 2025/09/01 15:08:15 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char *const argv[], t_env *env)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		while (argv[i + 1])
		{
			if (argv[i + 1][0])
				env_remove(env, argv[i + 1]);
			i++;
		}
	}
	return (0);
}
