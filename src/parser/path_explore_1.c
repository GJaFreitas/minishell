/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_explore_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:41:06 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 19:42:52 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static char	*__err(int *flag)
{
	*flag = UNKNOW_CMD;
	return (NULL);
}

char	*__rel_path_srch(char *token, int *flag)
{
	char	*folders[2];
	char	cwd[CWD_BUFFER];
	char	*path;

	folders[1] = NULL;
	ft_bzero(cwd, CWD_BUFFER);
	if (token[0] == '/')
		return (NULL);
	else if (token[0] == '.')
	{
		if (token[1] != '/')
			return (__err(flag));
		getcwd(cwd, CWD_BUFFER);
	}
	token = ft_strrchr(token, '/') + 1;
	folders[0] = cwd;
	path = __search_folders(folders, token);
	if (path == NULL)
		return (__err(flag));
	return (path);
}
