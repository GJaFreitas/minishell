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
