#include "minishell.h"

int	ft_pwd(char *const argv[], t_env *env)
{
	char	cwd[CWD_BUFFER];

	(void)argv;
	(void)env;
	if (!getcwd(cwd, CWD_BUFFER))
		exit(1);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	exit (0);
}
