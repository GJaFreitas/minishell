/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:22 by bag               #+#    #+#             */
/*   Updated: 2025/09/01 17:44:09 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	__check_num(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char *const argv[], t_env *env)
{
	int	exitcode;

	(void)env;
	(void)argv;
	if (count_args(argv) > 2)
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n", argv[1]);
		return (1);
	}
	if (!__check_num(argv[1]))
	{
		ft_fprintf(2, "minishell: exit: %s: numeric argument required\n", argv[1]);
		return (1);
	}
	if (argv[1])
		exitcode = ft_atoi(argv[1]);
	else
		exitcode = 0;
	exit (free_minishell(env, exitcode));
}
