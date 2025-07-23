#include "minishell.h"

static void	__print_env(char *const env[])
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		ft_printf("%s", env[i++]);
		write(1, "\n", 1);
	}
}

int	ft_env(char *const argv[], char *const env[])
{
	(void)argv;
	__print_env(env);
	exit(0);
}
