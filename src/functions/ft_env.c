#include "minishell.h"

int	ft_env(char *const argv[], t_env *env)
{
	(void)argv;
	env_print(env);
	return (0);
}
