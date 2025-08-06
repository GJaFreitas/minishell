#include "minishell.h"

int ft_unset(char *const argv[], t_env *env)
{
    int i;
    
	i = 0;
    while (argv[++i])
        remove_env_var(env, argv[i]);
    return (0);
}
