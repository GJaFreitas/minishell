/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:30:08 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/22 12:32:30 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__case_out(t_cmd *cmd, t_redirect *redir);
int	__case_out_append(t_cmd *cmd, t_redirect *redir);
int	__case_in(t_cmd *cmd, t_redirect *redir);
int	__switch(t_cmd *cmd, t_redirect *redir);

void	exec_builtin(t_cmd *cmd, t_env *env)
{
	static int (*jump_table[7])(char *const argv[], t_env *) = { \
		ft_echo,
		ft_cd,
		ft_pwd,
		ft_export,
		ft_unset,
		ft_env,
		ft_exit
	};

	if (cmd->builtin == UNKNOWN_COMMAND)
		return (printf("minishell: %s: command not found\n",
		*cmd->args), (void)0);
	jump_table[cmd->builtin - 1](cmd->args, env);
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
		redir = cmd->redirect;
		while (redir)
		{
			if (__switch(cmd, redir))
				return (perror("open"), -1);
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
		else
			*out = pipefd[1];
	}
	else
		*out = cur->redirect_out;
}

void	ft_exec(t_cmd *cmd, t_env *env, int in, int out)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork"));
	if (cmd->pid == 0) // Child process
	{
		if (in != 0 && dup2(in, STDIN_FILENO) == -1)
			perror("dup2 stdin");
		if (out != 1 && dup2(out, STDOUT_FILENO) == -1)
			perror("dup2 stdout");
		if (execve(cmd->args[0], cmd->args, env_to_array(env)) == -1)
		{
			perror("execve");
			exit(127);
		}
	}
}

void	ft_exec_all(t_cmd *cmd, t_env *env)
{
	t_cmd	*cur;
	int	in;
	int	out;
	int	pipefd[2];

	if (setup_redirections(cmd) < 0)
		return ;
	in = 0;
	cur = cmd;
	while (cur)
	{
		setup_pipes(cur, &in, &out, pipefd);
		if (cur->builtin != 0)
			exec_builtin(cur, env);
		else
			ft_exec(cur, env, in, out);
		if (cur->next)
			close(pipefd[1]);
		if (in != 0)
			close(in);
		if (out != 0)
			close(out);
		in = ((cur->next != NULL) * pipefd[0]);
		cur = cur->next;
	}
	cur = cmd;
	while (cur)
	{
		if (cur->pid)
			waitpid(cur->pid, (int *)0, 0);
		cur = cur->next;
	}
}
