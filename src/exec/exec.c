/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:30:08 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/09/05 20:16:16 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <dirent.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		__case_out(t_cmd *cmd, t_redirect *redir);
int		__case_out_append(t_cmd *cmd, t_redirect *redir);
int		__case_in(t_cmd *cmd, t_redirect *redir);
int		__switch(t_cmd *cmd, t_redirect *redir);

void	exec_builtin(t_cmd *cmd, t_env *env, int in, int out)
{
	int			stdin_fd;
	int			stdout_fd;
	DIR			*test;
	static int	(*jump_table[7])(char *const argv[], t_env *) = {ft_echo, ft_cd,
		ft_pwd, ft_export, ft_unset, ft_env, ft_exit};

	if (cmd->builtin == UNKNOWN_COMMAND)
	{
		unknow_cmd(cmd, test, env);
		return ;
	}
	if (cmd->next)
	{
		env->exit = 0;
		if (cmd->builtin == 4 && cmd->args[1])
			return ;
		else if (cmd->builtin == 7)
			return ;
	}
	dups(stdin_fd, stdout_fd, in, out);
	env->exit = jump_table[cmd->builtin - 1](cmd->args, env);
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	(close(stdin_fd), close(stdout_fd));
}

int	setup_redirections(t_cmd *cmd)
{
	t_cmd		*current;
	t_redirect	*redir;

	if (!cmd)
		return (-2);
	current = cmd;
	while (current)
	{
		current->redirect_in = 0;
		current->redirect_out = 1;
		redir = current->redirect;
		while (redir)
		{
			if (__switch(current, redir))
				return (-1);
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}

void	setup_pipes(t_cmd *cur, int *in, int *out, int pipefd[2])
{
	if (cur->redirect_in != 0)
	{
		if (*in != 0)
			close(*in);
		*in = cur->redirect_in;
	}
	if (cur->next)
	{
		if (pipe(pipefd) == -1)
			return (perror("pipe error"));
		if (cur->redirect_out == 1)
			*out = pipefd[1];
		else
			*out = cur->redirect_out;
	}
	else
		*out = cur->redirect_out;
}

void	ft_exec(t_cmd *cmd, t_env *env, int in, int out)
{
	int	i;

	i = 3;
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork"));
	if (cmd->pid != 0)
		return ;
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	if (in != 0 && dup2(in, STDIN_FILENO) == -1)
		perror("dup2 stdin");
	if (out != 1 && dup2(out, STDOUT_FILENO) == -1)
		perror("dup2 stdout");
	while (i < FOPEN_MAX)
		close(i++);
	execve(cmd->args[0], cmd->args, env_to_array(env));
	exit(0);
}

int	wait_pids(t_cmd *cmds, t_env *env)
{
	int	sig;
	int	status;

	status = INT_MIN;
	while (cmds)
	{
		signal(SIGINT, SIG_IGN);
		if (cmds->pid)
			waitpid(cmds->pid, &status, 0);
		signal(SIGINT, __sigint_h);
		if (WIFSIGNALED(status))
			sig = sig_response(sig, status);
		cmds = cmds->next;
	}
	if (status == INT_MIN)
		return (env->exit);
	if (WIFSIGNALED(status))
		return (sig + 128);
	if (status != env->exit)
		return (WEXITSTATUS(status));
	return (env->exit);
}
