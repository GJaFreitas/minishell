#include "minishell.h"
#include "structs.h"

unsigned int	next_div_8(unsigned int n)
{
	while (n % 8)
		n++;
	return (n);
}

void	refresh_cmd(t_cmdtbl *cmd)
{
	t_simplecmd	*current;

	while (cmd->cmds && *cmd->cmds)
	{
		current = *cmd->cmds;
		if (current->args)
			free(current->args);
		if (current->cmd)
			free(current->cmd);
		if (current->infile)
			free(current->infile);
		if (current->opts)
			free(current->opts);
		if (current->outfile)
			free(current->outfile);
		free(*cmd->cmds);
		cmd->cmds++;
	}
}
