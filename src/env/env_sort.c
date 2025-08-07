#include "minishell.h"

static void	__create_sorted_array(int *arr, char **keys, int size);
static void	env_create_sorted(t_env *env);

void	env_print_sorted(t_env *env)
{
	static char	declare[12] = "declare -x ";
	unsigned int	i;

	i = 0;
	env_create_sorted(env);
	while (i < env->used)
	{
		ft_printf("%s", declare);
		ft_printf("%s", env->keys[env->sorted[i]]);
		write(1, "=", 1);
		write(1, "\"", 1);
		ft_printf("%s", env->values[env->sorted[i]]);
		write(1, "\"\n", 2);
	}
}

static void	env_create_sorted(t_env *env)
{
	if (env->sorted)
		free(env->sorted);
	env->sorted = malloc(sizeof(int) * env->used);
	__create_sorted_array(env->sorted, env->keys, env->used);
}

static void	__create_sorted_array(int *arr, char **keys, int size)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	arr[j] = 0;
	while (j < size)
	{
		while (i < size)
		{
			if (ft_strcmp(keys[i], keys[arr[j]]) < 0)
				arr[j] = i;
			i++;
		}
		j++;
	}
}
