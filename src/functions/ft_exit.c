#include "minishell.h"
#include <fcntl.h>

//@TODO: Get exit to work by outputting EOF to stdin
int	ft_exit(char *const argv[], t_env *env)
{
	int	fd;

	(void)env;
	(void)argv;
	exit(0);
}
