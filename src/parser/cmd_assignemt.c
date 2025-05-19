#include "libft.h"
#include "parser.h"
#include "structs.h"

static int	__assign_command(t_simplecmd *cmd, char **tokens)
{
	int	i;

	i = 1;
	cmd->cmd = tokens[0];
	while (!is_pipe(tokens[i]))
	{
		if (ft_strchr(REDIRECT, tokens[i][0]))
			__redirection(cmd, tokens[i]);
		else if (tokens[i][0] == '-')
			__options(cmd, tokens[i]);
		else
			__args(cmd, tokens[i]);
	}
	return (i);
}

void	assign_cmds(t_simplecmd **cmdarray, char **tokens)
{
	unsigned int	tok;

	tok = 0;
	while (*cmdarray)
	{
		tok += __assign_command(*cmdarray, tokens + tok);
	}
}
