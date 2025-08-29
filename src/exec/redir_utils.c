#include "minishell.h"

int	__case_out(t_cmd *cmd, t_redirect *redir);
int	__case_out_append(t_cmd *cmd, t_redirect *redir);
int	__case_in(t_cmd *cmd, t_redirect *redir);
int	__case_hdoc(t_cmd *cmd, t_redirect *redir);

int	__switch(t_cmd *cmd, t_redirect *redir)
{		
	if (ft_strcmp(redir->args[0], ">") == 0 && __case_out(cmd, redir))
		return (1);
	else if (ft_strcmp(redir->args[0], ">>") == 0 && __case_out_append(cmd, redir))
		return (1);
	else if (ft_strcmp(redir->args[0], "<") == 0 && __case_in(cmd, redir))
		return (1);
	else if (ft_strcmp(redir->args[0], "<<") == 0 && __case_hdoc(cmd, redir))
		return (1);
	return (0);
}

int	__case_hdoc(t_cmd *cmd, t_redirect *redir)
{
	if (cmd->redirect_in != 0)
		close(cmd->redirect_in);
	cmd->redirect_in = heredoc(redir->args[1], cmd->args);
	if (cmd->redirect_in == -1)
		return (perror("heredoc"), 1);
	redir->args[1][0] = cmd->redirect_in;
	return (0);
}

int	__case_out(t_cmd *cmd, t_redirect *redir)
{            
	if (cmd->redirect_out != 1)
		close(cmd->redirect_out);
	cmd->redirect_out = open(redir->args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->redirect_out == -1)
		return (perror("open"), 1);
	return (0);
}

int	__case_out_append(t_cmd *cmd, t_redirect *redir)
{
	if (cmd->redirect_out != 1)
		close(cmd->redirect_out);
	cmd->redirect_out = open(redir->args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->redirect_out == -1)
		return (perror("open"), 1);
	return (0);
}

int	__case_in(t_cmd *cmd, t_redirect *redir)
{
	if (cmd->redirect_in != 0)
		close(cmd->redirect_in);
	cmd->redirect_in = open(redir->args[1], O_RDONLY);
	if (cmd->redirect_in == -1)
		return (perror("open"), 1);
	return (0);
}
