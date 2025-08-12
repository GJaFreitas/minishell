#include "minishell.h"

int	ft_cd(char *const argv[], t_env *env)
{
	char	*full_dir_path;

	full_dir_path = get_full_dir_path(argv + 1);
	if (path_exists(full_dir_path))
		chdir(full_dir_path);
	else
		printf("Error");
	(void)env;
	exit(0);
}
