#include "minishell.h"

int	ft_exit(char *const argv[], t_env *env)
{
	(void)env;
	(void)argv;
	write(1, "exit\n", 5);
	// This can just send a CTRL-D signal back to main
	exit(0);
}
