#include "libft.h"
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
		ft_printf("%s=", env->keys[i]);
		if (env->values[i])
			ft_printf("%s", env->values[i]);
		write(1, "\n", 1);
		i++;
	}
}

// Returns index of variable, -1 if it doesnt exist
int	env_var_exists(t_env *env, char *key)
{
	unsigned int	i;

	i = 0;
	if (!key)
		return (-1);
	while (i < env->used)
	{
		if (ft_strcmp(env->keys[i], key))
			return (i);
	}
	return (-1);
}

// Assumes valid index and value
void	env_change_val(t_env *env, int index, char *val)
{
	if (env->values[index])
		free(env->values[index]);
	env->values[index] = ft_strdup(val);
}
