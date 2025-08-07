#include "libft.h"
#include "minishell.h"
#include <string.h>

/*
 * Functionality:
 * 	Add
 * 	Remove
*/

void	env_add(t_env *env, char *key, char *value)
{
	unsigned int	used;

	used = env->used;
	if (used + 1 <= env->size)
		env_grow(env);
	env->keys[used] = ft_strdup(key);
	env->values[used] = ft_strdup(value);
	env->used++;
}

static void	__move_back(char **keys, char **values, int size);

void	env_remove(t_env *env, char *key)
{
	unsigned int	i;

	i = 0;
	while (i < env->used)
	{
		if (!ft_strcmp(env->keys[i], key))
		{
			__move_back(&env->keys[i], &env->values[i], env->used - i);
			env->used--;
		}
	}
}

static void	__move_back(char **keys, char **values, int size)
{
	int	i;

	i = 0;
	while (i + 1 < size)
	{
		keys[i] = keys[i + 1];
		values[i] = values[i + 1];
		i++;
	}
}
