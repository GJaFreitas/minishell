#include "minishell.h"

static void	__create_sorted_array(int *arr, char **keys, int size, int *used);
static void	env_create_sorted(t_env *env);

void	env_print_sorted(t_env *env)
{
	static char	declare[12] = "declare -x ";
	unsigned int	i;

	i = 0;
	env_create_sorted(env);
	return ;
	while (i < env->used)
	{
		ft_printf("%s", declare);
		ft_printf("%s", env->keys[env->sorted[i]]);
		write(1, "=", 1);
		write(1, "\"", 1);
		ft_printf("%s", env->values[env->sorted[i]]);
		write(1, "\"\n", 2);
		i++;
	}
}

static void	env_create_sorted(t_env *env)
{
	int	*temp;

	if (env->sorted)
		free(env->sorted);
	env->sorted = malloc(sizeof(int) * env->used);
	temp = ft_calloc(sizeof(int), (env->used + 1));
	__create_sorted_array(env->sorted, env->keys, env->used, temp);
	free(temp);
}

static void	__create_sorted_array(int *arr, char **keys, int size, int *used)
{
	int	i;
	int	j;

	j = 0;
	arr[j] = 1;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			if (!used[i] && ft_strcmp(keys[i], keys[arr[j]]) <= 0)
			{
				printf("CURRENT: %s\nNEXT: %s\n USED AT %d: %d\nj: %d\ni: %d\n", keys[arr[j]], keys[i], arr[j], used[arr[j]], j, i);
				printf("CONDITION\n");
				arr[j] = i;
			}
			i++;
		}
		used[arr[j]] = 1;
		j++;
	}
}
