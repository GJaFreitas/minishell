#include "libft.h"
#include "minishell.h"
#include <string.h>

/*
 * Functionality:
 * 	Add
 * 	Remove
*/

static void	__get_key_value(char *args, char **key, char **value);

// export var+="value"  -- VALID
// export var="$env_var"value -- VALID
// export var=$env_var"value" -- VALID
void	env_add(t_env *env, char *args)
{
	char	*key;
	char	*value;
	unsigned int	used;
	int	exists;

	__get_key_value(args, &key, &value);
	exists = env_var_exists(env, key);
	if (exists != -1)
	{
		env_change_val(env, exists, value);
		return ;
	}
	used = env->used;
	if (used + 1 <= env->size)
		env_grow(env);
	env->keys[used] = ft_strdup(key);
	env->values[used] = ft_strdup(value);
	env->used++;
	env->exported++;
}

static void	__get_key_value(char *args, char **key, char **value)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		if (args[i] == '=')
		{
			*key = ft_substr(args, 0, i);
			break ;
		}
		i++;
	}
	if (!args[++i])
	{
		*value = NULL;
		return ;
	}
	j = i;
	while (args[i++]);
	*value = ft_substr(args, j, i - j);
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
			if (is_exported(env, i))
				env->exported--;
			return ;
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
