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
	env_add_key_value_pair(env, "PWD", new);
	env_add_key_value_pair(env, "OLD_PWD", old);
}

int	ft_cd(char *const argv[], t_env *env)
{
	char	full_dir_path[CWD_BUFFER];
	char	current_dir[CWD_BUFFER];

	getcwd(current_dir, CWD_BUFFER);
	get_full_dir_path(*argv + 1, env, &full_dir_path);
	printf("PATH: %s\n", *full_dir_path);
	// if (path_exists(full_dir_path))
	// {
	// 	update_env(current_dir, full_dir_path, env);
	// 	chdir(full_dir_path);
	// }
	// else
	// 	printf("Placeholder error message");
	return (0); // TURN THIS INTO EXIT(0)
}
