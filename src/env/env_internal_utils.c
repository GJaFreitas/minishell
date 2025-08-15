#include "minishell.h"

void	env_grow(t_env *env)
{
	env->values = ft_realloc(env->values, env->size * sizeof(char *), env->size * 2* sizeof(char *));
	env->keys = ft_realloc(env->keys, env->size* sizeof(char *), env->size * 2* sizeof(char *));
	env->size *= 2;
}

void	print_env_debug(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->used)
	{
		ft_printf("%s=", env->keys[i]);
		if (env->values[i])
			ft_printf("%s", env->values[i]);
		write(1, "\n", 1);
	}
}
