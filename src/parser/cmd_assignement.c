#include "libft.h"
#include "parser.h"
#include "structs.h"

// Iterates over tokens until a pipe is found and fills up the
// simplecmd struct with info
static int	__assign_command(t_simplecmd *cmd, char **tokens)
{
	int	i;

	i = 1;
	cmd->cmd = ft_strdup(tokens[0]);
	while (tokens[i] && !is_pipe(tokens[i]))
	{
		if (ft_strchr(REDIRECT, tokens[i][0]))
			i += __redirections(cmd, &tokens[i]);
		else if (tokens[i][0] == '-')
			__options(cmd, tokens[i]);
		else
			__args(cmd, tokens[i]);
		i++;
	}
	return (i);
}

void	assign_cmds(t_simplecmd **cmdarray, char **tokens, t_uint count)
{
	unsigned int	tok;

	tok = 0;
	while (tok < count)
	{
		tok += __assign_command(*cmdarray, tokens + tok);
	}
}
