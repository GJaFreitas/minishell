/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:14:47 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/09/05 19:14:59 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <dirent.h>
#include <limits.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_exec_all(t_cmd *cmd, t_env *env)
{
	t_cmd	*cur;
	int		in;
	int		out;
	int		pipefd[2];

	if (setup_redirections(cmd) < 0)
		return (1);
	in = 0;
	cur = cmd;
	while (cur)
	{
		setup_pipes(cur, &in, &out, pipefd);
		if (cur->builtin != 0)
			exec_builtin(cur, env, in, out);
		else
			ft_exec(cur, env, in, out);
		if (cur->next && cur->redirect_out != 1
			&& cur->redirect_out != pipefd[1])
			close(pipefd[1]);
		else if (cur->next && cur->builtin < 1)
			close(pipefd[1]);
		if (in != 0)
			close(in);
		if (out != 1 && out != pipefd[1])
			close(out);
		in = ((cur->next != NULL) * pipefd[0]);
		cur = cur->next;
	}
	return (wait_pids(cmd, env));
}