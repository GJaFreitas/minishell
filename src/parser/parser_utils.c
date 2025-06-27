#include "minishell.h"
#include "parser.h"

t_cmd	*__init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(struct s_cmd));
	cmd->redirect_in = -1;
	cmd->redirect_out = -1;
	return (cmd);
}

int	is_pipe(char *token)
{
	return (*token == '|');
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
}

void	free_cmds(t_cmd *cmds)
{
	t_redirect	*cur;
	t_cmd		*next;

	next = cmds;
	while (next)
	{
		cmds = next;
		free_tokens(cmds->args);
		free(cmds->args);
		while (cmds->redirect)
		{
			cur = cmds->redirect;
			free(cur->args[0]);
			free(cur->args[1]);
			cmds->redirect = cur->next;
			free(cur);
		}
		next = cmds->next;
		free(cmds);
	}
}
