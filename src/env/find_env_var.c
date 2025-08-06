#include "minishell.h"

t_env	*find_env_var(t_env *env, char *var)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (!ft_strcmp(var, cur->key))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
