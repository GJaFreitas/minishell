#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <dirent.h>

/*
	!dir_stream && folders++
	will only reach the folders++ instruction
	if dir_stream == NULL which is fine :)
	(trick from bash scripting with regex)
*/

static char	*__search_folders(char **folders, char *token)
{
	struct dirent	*entry;
	char		*path;
	DIR		*dir_stream;

	path = NULL;
	while (*folders)
	{
		dir_stream = opendir(*folders);
		if (!dir_stream && folders++)
			continue ;
		entry = readdir(dir_stream);
		while (entry)
		{
			if (!ft_strncmp(entry->d_name, token, ft_strlen(token)))
			{
				path = ft_strdup(*folders);
				closedir(dir_stream);
				return (path);
			}
			entry = readdir(dir_stream);
		}
		closedir(dir_stream);
		folders++;
	}
	return (path);
}

// Evil ass function because of norm
static char	**__get_folders(char *path)
{
	char	**folders;
	char	*temp;
	int	i;
	int	total;

	i = 0;
	total = 1;
	while (path && path[i])
		if (path[i++] == ':')
			total++;
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

char	*path_search(char *token, char **env)
{
	char	**folders;
	char	*path;
	char	*path_env_var;
	char	*temp;

	path_env_var = __path_extract(env);
	if (!path_env_var)
		return (perror("PATH not set\n"), NULL);
	folders = __get_folders(path_env_var);
	path = __search_folders(folders, token);
	if (path == NULL)
	{
		free_tokens(folders);
		free(folders);
		return (ft_strdup("Cmd not found"));
	}
	temp = ft_strjoin(path, "/");
	free(path);
	path = ft_strjoin(temp, token);
	free_tokens(folders);
	free(folders);
	return (path);
}
