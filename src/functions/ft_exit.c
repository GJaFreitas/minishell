#include "minishell.h"

int	ft_exit(char *const argv[], char *const env[])
{
	(void)env;
	(void)argv;
	write(1, "exit\n", 5);
	exit(0);
}
