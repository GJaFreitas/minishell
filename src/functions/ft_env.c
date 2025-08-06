#include "minishell.h"

int	ft_env(char *const argv[], t_env *env)
{
	t_env	*current;

	(void)argv;
	current = env;
	while (current)
	{
		if (current->exported && current->value[0] != '\0')
			ft_printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
