/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:30:08 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/07/23 17:18:23 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
int	__case_out(t_cmd *cmd, t_redirect *redir);
int	__case_out_append(t_cmd *cmd, t_redirect *redir);
int	__case_in(t_cmd *cmd, t_redirect *redir);
int	__switch(t_cmd *cmd, t_redirect *redir);

void	exec_builtin(t_cmd *cmd, char **env)
{
	static int (*jump_table[7])(char *const argv[], char *const env[]) = { \
		ft_echo,
		ft_cd,
		ft_pwd,
		ft_export,
		ft_unset,
		ft_env,
		ft_exit
	};

	jump_table[cmd->builtin - 1](&cmd->args[1], env);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
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
	t_redirect *redir;

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
	return (0);
}

void	ft_exec(t_cmd *cmd, int in, int out, char **env)
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
	if (cmd->builtin > 0)
		exec_builtin(cmd, env);
	else if (execve(cmd->args[0], cmd->args, env) == -1)
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

void	ft_exec_all(t_cmd *cmd, char **env)
{
    int in, out;
    int fd[2];
    t_cmd *current;
    
    if (!cmd)
        return;
    current = cmd;
    while (current)
    {
        if (setup_redirections(current) == -1)
            return;
        current = current->next;
    }
    current = cmd;
    in = 0;
    
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
            {
                perror("pipe");
                return;
            }
            out = fd[1];
        }
        else
            out = (current->redirect_out != 1) ? current->redirect_out : 1;
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
