/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:30:08 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/18 15:51:30 by bag              ###   ########.fr       */
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

	jump_table[cmd->builtin - 1](cmd->args, env);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if ((!s1 && s2) || (!s2 && s1))
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
		cmd->redirect_in = 0;   // stdin
		cmd->redirect_out = 1;  // stdout
		redir = cmd->redirect;
		while (redir)
		{
			// Esta tudo na file redir_utils.c
			if (__switch(cmd, redir))
				return (perror("open"), -1);
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}

void	ft_exec(t_cmd *cmd, int in, int out, t_env *env)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork"));
	if (cmd->pid == 0) // Child process
	{
		if (in != 0)
		{
			if (dup2(in, STDIN_FILENO) == -1)
				perror("dup2 stdin");
			close(in);
		}
		if (out != 1)
		{
			if (dup2(out, STDOUT_FILENO) == -1)
				perror("dup2 stdout");
			close(out);
		}
		if (execve(cmd->args[0], cmd->args, env_to_array(env)) == -1)
		{
			perror("execve");
			exit(127);
		}
	}
	else // need to remove after tests
	{
		if (in != 0)
			close(in);
		if (out != 1)
			close(out);
	}
}

void	ft_exec_all(t_cmd *cmd, t_env *env)
{
	t_cmd	*current;
	int	in;
	int	out;
	int	fd[2];

	if (setup_redirections(cmd) < 0)
		return ;
	in = 0;
	current = cmd;
	while (current)
	{
		if (current->redirect_in != 0)
		{
			if (in != 0)
				close(in);
			in = current->redirect_in;
		}
		if (current->next)
		{
			if (pipe(fd) == -1)
				return (perror("pipe error"));
			else
				out = fd[1];
		}
		else
			out = current->redirect_out;
		if (current->builtin > 0)
			exec_builtin(cmd, env);
		else
			ft_exec(current, in, out, env);
		if (current->next)
			close(fd[1]);
		if (in != 0)
			close(in);
		in = (current->next) ? fd[0] : 0;

		current = current->next;
	}

	// Wait for all children to complete
	current = cmd;
	while (current)
	{
		int status;
		waitpid(current->pid, &status, 0);
		current = current->next;
	}
}
