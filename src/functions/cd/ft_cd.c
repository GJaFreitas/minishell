/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:22 by bag               #+#    #+#             */
/*   Updated: 2025/08/30 19:47:34 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
* cd -
* cd ~
* unset HOME -> cd ~
* cd with relative path and absolute path
*
* to free the prev_path and new one call cd with "this makes no sense"
* as the args
*/

void	update_env(char *old, char *new, t_env *env)
{
	if (new[ft_strlen(new) - 1] == '/')
		new[ft_strlen(new) - 1] = 0;
	env_add_key_value_pair(env, "PWD", new);
	env_add_key_value_pair(env, "OLD_PWD", old);
}

// flag is only for when the $HOME env variable is unset
int	ft_cd(char *const argv[], t_env *env)
{
	char	full_dir_path[CWD_BUFFER];
	char	current_dir[CWD_BUFFER];
	int	flag;

	flag = 0;
	getcwd(current_dir, CWD_BUFFER);
	ft_bzero(full_dir_path, CWD_BUFFER);
	if (argv[1])
		flag = get_full_dir_path(argv[1], env, &full_dir_path);
	else
		flag = get_full_dir_path("~", env, &full_dir_path);
	if (path_exists(full_dir_path))
	{
		update_env(current_dir, full_dir_path, env);
		chdir(full_dir_path);
	}
	else if (!flag)
		printf("minishell: cd: %s: No such file or directory\n", argv[1]);
	return (0);
}
