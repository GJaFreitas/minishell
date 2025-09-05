/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_assignement_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:45:52 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 19:45:59 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	__arg_count(char **tokens)
{
	int	i;

	i = 1;
	while (*tokens)
	{
		if (is_pipe(*tokens))
			return (i);
		if (!ft_strchr(REDIRECT, **tokens))
			i++;
		tokens++;
	}
	return (i);
}

t_cmd	*assign_cmds(char **tokens, char **env)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = __init_cmd();
	current = cmds;
	while (*tokens)
	{
		current->args = ft_calloc(__arg_count(tokens) + 1, sizeof(char *));
		tokens += __assign_command(current, tokens, env);
		if (*tokens)
		{
			current->next = __init_cmd();
			current = current->next;
		}
	}
	return (cmds);
}
