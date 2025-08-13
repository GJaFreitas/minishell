#include "minishell.h"
#include <dirent.h>

// Assume path is a nul terminated string and not NULL
int	path_exists(char *path)
{
	struct dirent	*entry;
	DIR		*dir_stream;
	int		ret;

	dir_stream = opendir(path);
	ret = (dir_stream != 0);
	closedir(dir_stream);
	return (ret);
}
