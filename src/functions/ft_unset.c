#include "minishell.h"

int	ft_unset(char *const argv[], t_env *env)
{
	if (argv[1])
		env_remove(env, argv[1]);
	print_tokens(env->keys);
	exit(0);
}
