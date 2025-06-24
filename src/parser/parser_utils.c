#include "parser.h"

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
	if (!cmds)
		return ;
	while (cmds)
	{
		free_tokens(cmds->args);
		while (cmds->redirect)
		{
			free(cmds->redirect->args[0]);
			free(cmds->redirect->args[1]);
			cmds->redirect = cmds->redirect->next;
		}
		cmds = cmds->next;
	}
}
