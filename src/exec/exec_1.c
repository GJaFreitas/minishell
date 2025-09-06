/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:14:47 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/09/06 17:15:03 by gvon-ah-         ###   ########.fr       */
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

static void	ft_exec_closes(t_cmd *cur, int pipefd[2], int in, int out);

int	ft_exec_all(t_cmd *cmd, t_env *env)
{
	t_cmd	*cur;
	int		in;
	int		out;
	int		pipefd[2];

	pipefd[0] = -1;
	pipefd[1] = -1;
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
		ft_exec_closes(cur, pipefd, in, out);
		in = ((cur->next != NULL) * pipefd[0]);
		cur = cur->next;
	}
	return (wait_pids(cmd, env));
}

static void	ft_exec_closes(t_cmd *cur, int pipefd[2], int in, int out)
{
	if (cur->next)
		close(pipefd[1]);
	if (in != 0)
		close(in);
	if (out != 1 && out != pipefd[1])
		close(out);
}

int	sig_response(int sig, int status)
{
	sig = WTERMSIG(status);
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
		write(2, "Quit (core dumped)\n", 20);
	return (sig);
}

void	dups(int *stdin_fd, int *stdout_fd, int in, int out)
{
	*stdin_fd = dup(STDIN_FILENO);
	*stdout_fd = dup(STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	unknow_cmd(t_cmd *cmd, t_env *env)
{
	DIR			*test;

	test = opendir(cmd->args[0]);
	if (test)
		ft_fprintf(2, "minishell: %s: Is a directory\n", *cmd->args);
	else
		ft_fprintf(2, "minishell: %s: command not found\n", *cmd->args);
	env->exit = 127 - ((closedir(test) == 0));
}
