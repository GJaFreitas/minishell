#include "minishell.h"

// Get value for a given key
char	*env_get_value(t_env *env, char *key)
{
	unsigned int	i;

	if (!key)
		return (NULL);
	i = 0;
	while (i < env->used)
	{
		if (!ft_strcmp(env->keys[i], key))
			return (env->values[i]);
		i++;
	}
	return (NULL);
}

void	env_print(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->used)
	{
		ft_printf("%s", env->keys[i]);
		write(1, "=", 1);
		ft_printf("%s", env->values[i]);
	}
}
