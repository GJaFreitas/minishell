/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:22 by bag               #+#    #+#             */
/*   Updated: 2025/08/30 19:47:36 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *const argv[], t_env *env)
{
	int	exitcode;

	(void)env;
	(void)argv;
	if (argv[1])
		exitcode = ft_atoi(argv[1]);
	else
		exitcode = 0;
	exit (free_minishell(env, exitcode));
}
