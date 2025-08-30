/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/08/30 19:47:39 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"

static void	__rm_quote_arg(char *arg)
{
	while (*arg)
	{
		if (ft_strchr(QUOTES, *arg))
			ft_memcpy(arg, arg + 1, ft_strlen(arg + 1) + 1);
		else
			arg++;
	}
}

static void	__remove_quotes(t_cmd *cmds)
{
	int	i;

	while (cmds)
	{
		i = 0;
		while (cmds->args[i])
			__rm_quote_arg(cmds->args[i++]);
		cmds = cmds->next;
	}
}

t_cmd	*parser(char **tokens, t_env *env, char **env_array)
{
	t_cmd		*cmds;

	if (tokens == NULL)
		return (NULL);
	heredocs(tokens, env_array);
	expansions(tokens, env_array, env->exit);
	cmds = assign_cmds(tokens, env_array);
	__remove_quotes(cmds);
	free_tokens(tokens);
	free(tokens);
	return (cmds);
}
