#include "minishell.h"

int	ft_exit(char *const argv[], char *const env[])
{
	(void)env;
	exit(ft_atoi(argv[0]));
}
