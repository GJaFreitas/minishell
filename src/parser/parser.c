/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 20:05:06 by bag              ###   ########.fr       */
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

// Requires 2 branches:
// 	- Relative file path -> "./file" "/bin/file"
// 	- file in $PATH var  -> "cat" "ls"
char	*path_search(char *token, char **env, enum e_builtin *cmd)
{
	int		flag;
	char	*res;
	char	*temp;

	flag = 0;
	if (ft_strchr("/.", token[0]))
		res = __rel_path_srch(token, &flag);
	else
		res = __env_path_srch(token, env, &flag);
	if (flag == -1)
		*cmd = NO_BUILTIN;
	else if (flag == UNKNOW_CMD)
		*cmd = UNKNOWN_COMMAND;
	if (res == NULL)
		return (ft_strdup(token));
	temp = ft_strjoin(res, "/");
	free(res);
	res = ft_strjoin(temp, token);
	free(temp);
	return (res);
}
