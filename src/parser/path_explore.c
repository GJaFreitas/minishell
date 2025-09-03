/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_explore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/09/03 19:41:32 by bag              ###   ########.fr       */
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
	int		i;

	path = NULL;
	i = count_args(folders);
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
	temp = path + i - 1;
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
	(!path_env_var) && (*flag = NO_PATH_VAR);
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
		*flag = NO_PATH_VAR;
		return (NULL);
	}
	return (path);
}

// Requires 2 branches:
// 	- Relative file path -> "./file" "/bin/file"
// 	- file in $PATH var  -> "cat" "ls"
char	*path_search(char *token, char **env, enum e_builtin *cmd)
{
	int		flag;
	char	*res;
	char	*temp;

	flag = 0;
	if (ft_strchr("/.", token[0]))
		res = __rel_path_srch(token, &flag);
	else
		res = __env_path_srch(token, env, &flag);
	if (flag == -1)
		*cmd = NO_BUILTIN;
	else if (flag == UNKNOW_CMD)
		*cmd = UNKNOWN_COMMAND;
	if (res == NULL)
		return (ft_strdup(token));
	temp = ft_strjoin(res, "/");
	free(res);
	res = ft_strjoin(temp, token);
	free(temp);
	return (res);
}
