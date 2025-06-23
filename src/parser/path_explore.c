#include "libft.h"
#include "minishell.h"
#include "parser.h"

// Returns a ptr to the line with 'PATH'
static char	*path_extract(char **env)
{
	while (*env && !ft_strncmp(*env, "PATH", 4))
		env++;
	return (*env);
}

char	*path_search(char *token, char **env)
{
	char	**folders;
	char	*path;
	char	*ret;

	path = path_extract(env);
	return (ret);
}
