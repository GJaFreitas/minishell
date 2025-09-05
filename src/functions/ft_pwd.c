/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:22 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 19:28:28 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char *const argv[], t_env *env)
{
	char	cwd[CWD_BUFFER];

	(void)argv;
	(void)env;
	if (!getcwd(cwd, CWD_BUFFER))
		return (1);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	return (0);
}
