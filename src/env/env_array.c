#include "minishell.h"

static char	*__strjoin_mod(char *s1, char *s2);

char	**env_to_array(t_env *env)
{
	char	**arr;
	unsigned int	i;

	arr = malloc(sizeof(char *) * (env->used + 1));
	i = 0;
	while (i < env->used)
	{
		arr[i] = __strjoin_mod(env->keys[i], env->values[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	free_env_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

// +1 -> '='  +1 -> '\0'
static char	*__strjoin_mod(char *s1, char *s2)
{
	char	*new;
	int	i;
	int	j;

	new = malloc(ft_strlen(s1) + ft_strlen(s1) + 1 + 1);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = i + 1;
	new[j++] = '=';
	i = -1;
	while (s2[++i])
		new[j++] = s1[i];
	return (new);
}
