#include "minishell.h"

int ft_unset(char *const argv[], t_env *env)
{
    int i;
    
	i = 0;
    while (args[++i])
        remove_env_var(env_list, args[i]);
    return (0);
}
