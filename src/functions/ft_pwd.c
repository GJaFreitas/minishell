#include "minishell.h"

int	ft_pwd(void)
{
	char	cwd[CWD_BUFFER];

	if (!getcwd(cwd, CWD_BUFFER))
		return (1);
	write(1, cwd, ft_strlen(cwd));
	return (0);
}
