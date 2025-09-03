/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:30:08 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/09/03 17:38:23 by bag              ###   ########.fr       */
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

int		__case_out(t_cmd *cmd, t_redirect *redir);
int		__case_out_append(t_cmd *cmd, t_redirect *redir);
int		__case_in(t_cmd *cmd, t_redirect *redir);
int		__switch(t_cmd *cmd, t_redirect *redir);

void	exec_builtin(t_cmd *cmd, t_env *env, int in, int out)
{
	int	stdin_fd;
	int	stdout_fd;
	DIR	*test;
	static int (*jump_table[7])(char *const argv[], t_env *) = {ft_echo, ft_cd,
		ft_pwd, ft_export, ft_unset, ft_env, ft_exit};

	if (cmd->builtin == UNKNOWN_COMMAND)
	{
		test = opendir(cmd->args[0]);
		if (test)
			ft_fprintf(2, "minishell: %s: Is a directory\n", *cmd->args);
		else
			ft_fprintf(2, "minishell: %s: command not found\n", *cmd->args);
		env->exit = 127 - ((closedir(test) == 0));
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
	stdin_fd = dup(STDIN_FILENO);
	stdout_fd = dup(STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
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
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				write(1, "\n", 1);
			else if (sig == SIGQUIT)
				write(2, "Quit (core dumped)\n", 20);
		}
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
		// print_one_cmd(cur);
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
