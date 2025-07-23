#include "minishell.h"

int	ft_pwd(char *const argv[], char *const env[])
{
	char	cwd[CWD_BUFFER];

	(void)argv;
	(void)env;
	if (!getcwd(cwd, CWD_BUFFER))
		return (1);
	write(1, cwd, ft_strlen(cwd));
	return (0);
}
