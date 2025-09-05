/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 18:43:31 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"

void	__rm_quote_arg(char *arg)
{
	char	temp;

	temp = 0;
	while (*arg)
	{
		if (ft_strchr(QUOTES, *arg))
		{
			temp = *(ft_strchr(QUOTES, *arg));
			ft_memcpy(arg, arg + 1, ft_strlen(arg + 1) + 1);
			while (*arg && *arg != temp)
				arg++;
		}
		else
			arg++;
	}
}

static void	__remove_quotes(t_cmd *cmds, int flag)
{
	int	i;

	while (cmds)
	{
		i = 0;
		if (flag && !ft_strcmp(cmds->args[0], "export"))
			;
		else
			while (cmds->args && cmds->args[i])
				__rm_quote_arg(cmds->args[i++]);
		cmds = cmds->next;
	}
}

t_cmd	*parser(char **tokens, t_env *env, char **env_array)
{
	t_cmd	*cmds;

	if (tokens == NULL)
		return (NULL);
	heredocs(tokens, env);
	expansions(tokens, env_array, env->exit);
	cmds = assign_cmds(tokens, env_array);
	__remove_quotes(cmds, 1);
	free_tokens(tokens);
	free(tokens);
	norm(cmds);
	return (cmds);
}
