/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_assignement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 20:15:41 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"

static t_redirect	*__redirect(t_redirect *redir, char **tokens, int *i)
{
	t_redirect	*cur;

	if (!redir)
	{
		redir = ft_calloc(1, sizeof(struct s_redirect));
		redir->args[0] = ft_strdup(tokens[0]);
		redir->args[1] = ft_strdup(tokens[1]);
		cur = redir;
	}
	else
	{
		cur = redir;
		while (cur->next)
			cur = cur->next;
		cur->next = ft_calloc(1, sizeof(struct s_redirect));
		cur = cur->next;
		cur->args[0] = ft_strdup(tokens[0]);
		cur->args[1] = ft_strdup(tokens[1]);
	}
	*i += 1 + (cur->args[1][0] != 0);
	return (redir);
}

static enum e_builtin	is_builtin(enum e_builtin *cmd, char *token)
{
	static char	*builtins[8] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};
	int			i;

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(token, builtins[i]))
		{
			*cmd = i + 1;
			return (1);
		}
		i++;
	}
	*cmd = 0;
	return (0);
}

static void	__norm_help(t_cmd *cmd, char **tokens, char **env, int tok_index)
{
	if (!is_builtin(&cmd->builtin, tokens[tok_index]))
		cmd->args[0] = path_search(tokens[tok_index], env, &cmd->builtin);
	else
		cmd->args[0] = ft_strdup(tokens[tok_index]);
}

int	assign_command(t_cmd *cmd, char **tokens, char **env)
{
	int	i;
	int	tok_index;

	i = 0;
	tok_index = -1;
	while (tokens[++tok_index])
	{
		if (is_pipe(tokens[tok_index]))
			return (tok_index + 1);
		else if (tokens[tok_index][0] && ft_strchr(REDIRECT,
				tokens[tok_index][0]))
		{
			cmd->redirect = __redirect(cmd->redirect, &tokens[tok_index], &i);
			(void)((cmd->redirect->args[1][0]) && tok_index++);
		}
		else if (tokens[tok_index][0] && i == 0 && ++i)
			__norm_help(cmd, tokens, env, tok_index);
		else
			cmd->args[i++] = ft_strdup(tokens[tok_index]);
	}
	return (i);
}
