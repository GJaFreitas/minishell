#include "minishell.h"

static void	__create_sorted_array(int *arr, char **keys, int size, int *used);
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
		i++;
	}
}

static void	env_create_sorted(t_env *env)
{
	int	*temp;

	if (env->sorted)
		free(env->sorted);
	env->sorted = malloc(sizeof(int) * env->used);
	temp = ft_calloc((env->used + 1), sizeof(int));
	__create_sorted_array(env->sorted, env->keys, env->used, temp);
	free(temp);
}

static void	__create_sorted_array(int *arr, char **keys, int size, int *used)
{
	int	i;
	int	j;
	int	cur;

	j = 0;
	while (j < size)
	{
		i = 0;
		cur = j;
		while (i < size)
		{
			while (i < size && used[i] == 1)
				i++;
			if (i < size && ft_strcmp(keys[i], keys[j]) < 0)
				cur = i;
			i++;
		}
		arr[j] = cur;
		used[cur] = 1;
		j++;
	}



	// for (int i = 0; i < size; i++)
	// 	printf("used[%d]: %d\n", i, used[i]);
	// for (int i = 0; i < size; i++)
	// 	printf("arr[%d]: %d\n", i, arr[i]);
	// for (int i = 0; i < size; i++)
	// 	printf("keys[%d]: %s\n", arr[i], keys[arr[i]]);
}
