#include "libft.h"
#include "parser.h"
#include "structs.h"

// Assigns in and out files and flags their existence
int	__redirections(t_simplecmd *cmd, char **tokens)
{
	if (**tokens == '<' || !ft_strncmp(*tokens, "<<", 2))
	{
		cmd->infile = ft_strdup(*(tokens + 1));
		if (!cmd->ior)
			cmd->ior = INFILE;
		else
			cmd->ior = IOFILES;
	}
	else if (**tokens == '>' || !ft_strncmp(*tokens, ">>", 2))
	{
		cmd->outfile = ft_strdup(*(tokens + 1));
		if (!cmd->ior)
			cmd->ior = OUTFILE;
		else
			cmd->ior = IOFILES;
	}
	return (1);
}
