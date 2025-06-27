#include "minishell.h"

static void	__print_env(char *const env[])
{
	static	char[] = {"declare -x "};

	
}

int	ft_export(char *const argv[], char *const env[])
{
	if (!argv || !*argv)
		return (__print_env(), 0);
	return (0);
}
