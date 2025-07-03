#include "minishell.h"


static void	ft_exec(t_cmd *cmd, int in, int out, char **env)
{
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		dup2(in, 0);
		close(in);
		dup2(out, 1);
		close(out);
		if (execve(cmd->args[0], cmd->args, env) == -1)
			exit(127);
	}
	close(in);
	close(out);
}
static void wait_all(t_cmd *cmd)
{
	int status;

	status = 0;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		status = WEXITSTATUS(status);
		cmd = cmd->next;
	}
}

void	ft_exec_all(t_cmd *cmd, char **env)
{
	int in;
	int out;
	int fd[2];
	t_cmd *tmp;

	in = dup(0);
	tmp = cmd;
	while (cmd)
	{
		print_cmd(cmd);
		out = dup(1);
		if (cmd->next && pipe(fd) != -1)
		{
			close(out);
			out = fd[1];
		}
		if (cmd->redirect_out)
			out = if_redirect(cmd,1,out);
		if (cmd->redirect_in)
			in = if_redirect(cmd,2,in);
		ft_exec(cmd, in, out, env);
		if (cmd->next)
		{
			close(in);
			in = fd[0];
		}
		cmd = cmd->next;
	}
	wait_all(tmp);
}


int if_redirect(t_cmd *cmd,int redirect,int input)
{
	close(input);
	if (redirect == 1)
		input = cmd->redirect_out;
	if (redirect == 2)
		input = cmd->redirect_in;
	return (input);
}
