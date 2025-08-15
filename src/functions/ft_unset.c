#include "minishell.h"

int	ft_unset(char *const argv[], t_env *env)
{
	if (argv[1])
		env_remove(env, argv[1]);
	exit(0);
}
