/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_explore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 19:07:42 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <dirent.h>
#include <unistd.h>

static char	*__search_folders(char **folders, char *token)
{
	struct dirent	*entry;
	char			*path;
	DIR				*dir_stream;
	int				i;

	(path = NULL, i = count_args(folders));
	while (--i >= 0)
	{
		dir_stream = opendir(folders[i]);
		if (!dir_stream && folders[i])
			continue ;
		entry = readdir(dir_stream);
		while (entry)
		{
			if (!ft_strcmp(entry->d_name, token))
			{
				(path = ft_strdup(folders[i]), closedir(dir_stream));
				return (path);
			}
			entry = readdir(dir_stream);
		}
		closedir(dir_stream);
	}
	return (path);
}

// Evil ass function because of norm
static char	**__get_folders(char *path)
{
	char	**folders;
	char	*temp;
	int		i;
	int		total;

	i = 0;
	total = 1;
	while (path && path[i])
		if (path[i++] == ':')
			total++;
	path = (ft_strchr(path, '=') + 1);
	folders = ft_calloc(total + 1, sizeof(char *));
	temp = &path[ft_strlen(path)];
	while (temp && (temp != path))
	{
		if (*temp == ':')
		{
			*folders++ = ft_substr(temp + 1, 0, (path + i) - temp);
			i = temp - path - 1;
		}
		temp--;
	}
	*folders++ = ft_substr(path, 0, ++i);
	return (folders - total);
}

// Returns a ptr to the line with 'PATH'
static char	*__path_extract(char **env)
{
	while (*env && ft_strncmp(*env, "PATH", 4))
		env++;
	return (*env);
}

static char	*__env_path_srch(char *token, char **env, int *flag)
{
	char	**folders;
	char	*path;
	char	*path_env_var;

	path_env_var = __path_extract(env);
	(!path_env_var) && (*flag = UNKNOW_CMD);
	if (!path_env_var)
		return (NULL);
	folders = __get_folders(path_env_var);
	path = __search_folders(folders, token);
	if (path == NULL)
	{
		free_tokens(folders);
		free(folders);
		*flag = UNKNOW_CMD;
		return (NULL);
	}
	(free_tokens(folders), free(folders));
	return (path);
}

static char	*__rel_path_srch(char *token, int *flag)
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
		{
			*flag = UNKNOW_CMD;
			return (NULL);
		}
		getcwd(cwd, CWD_BUFFER);
	}
	token = ft_strrchr(token, '/') + 1;
	folders[0] = cwd;
	path = __search_folders(folders, token);
	if (path == NULL)
	{
		*flag = UNKNOW_CMD;
		return (NULL);
	}
	return (path);
}
