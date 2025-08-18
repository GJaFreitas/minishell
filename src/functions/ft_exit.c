#include "minishell.h"

int	ft_exit(char *const argv[], t_env *env)
{
	int	exitcode;

	(void)env;
	(void)argv;
	if (argv[1])
		exitcode = ft_atoi(argv[1]);
	else
		exitcode = 0;
	exit (free_minishell(env, exitcode));
}
