#include "libft.h"
#include "minishell.h"

/*
 * Functionality:
 * 	Initialize
 * 	Free
*/

static char	*__extract_to_from(char *str, char end, char start);

t_env	*init_env(char **old)
{
	t_env	*env;
	unsigned int	i;

	env = malloc(sizeof(t_env));
	env->size = ENV_INIT_SIZE;
	env->keys = malloc(ENV_INIT_SIZE * sizeof(char *));
	env->values = malloc(ENV_INIT_SIZE * sizeof(char *));
	env->sorted = NULL;
	i = 0;
	while (*old)
	{
		env->keys[i] = __extract_to_from(*old, '=', -1);
		env->values[i] = __extract_to_from(*old, '\0', '=');
		old++;
		i++;
		if (i > env->size)
			env_grow(env);
	}
	env->used = i;
	return (env);
}

void	env_grow(t_env *env)
{
	env->values = ft_realloc(env->values, env->size, env->size * 2);
	env->size *= 2;
}

/*
 * start == -1 -> Desde o inicio
*/
static char	*__extract_to_from(char *str, char end, char start)
{
	int	i;

	i = 0;
	while (start != -1 && str[i++] != start);
	str += i;
	while (str[i] && str[i] != end)
		i++;
	return (ft_substr(str, 0, i));
}

// Doesnt free the env pointer itself
void	env_free(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->used)
	{
		free(env->keys[i]);
		free(env->values[i]);
		i++;
	}
	free(env->keys);
	free(env->values);
	if (env->sorted)
		free(env->sorted);
}
