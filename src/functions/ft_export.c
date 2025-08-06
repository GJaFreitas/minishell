/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:53:48 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/06 16:30:51 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_export(char *const argv[], t_env *env)
{
	(void)argv;
	(void)env;
	printf("Implement export\n");
	exit(0);
	// static t_ivar	**_ivars;
	// char	*new_entry;
	//
	// if (!argv || !*argv)
	// 	return (__print_env(env), 0);
	// while (*argv)
	// {
	// 	new_entry = __create_string(argv);
	// 	if (new_entry == NULL)
	// 		continue ;
	// 	if (ft_strchr(new_entry, '='))
	// 		__env_set(env, new_entry);
	// 	else
	// 		__internal_var(env, _ivars, new_entry);
	// 	argv++;
	// }
	// return (0);
	return(ft_export_l(argv, env));
}
