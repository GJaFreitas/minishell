/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 18:43:31 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

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

// Esta funcao podia ser free_tokens(char ***tokens) e
// tambem dava free ao proprio apontador mas era preciso
// ter cuidado e passar o apontador verdadeiro, nao sei
// se nao fica menos intuitivo
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
