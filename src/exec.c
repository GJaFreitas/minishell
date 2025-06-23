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
	printf("status: %i\n", status);
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
		out = dup(1);
		if (cmd->next && pipe(fd) != -1)
		{
			close(out);
			out = fd[1];
		}
		if (cmd->redirect_out)
		{
			close(out);
			out = cmd->redirect_out;
		}
		if (cmd->redirect_in)
		{
			close(in);
			in = cmd->redirect_in;
		}
		ft_exec(cmd, in, out, env);
		if (cmd->next)
		{
			close(in);
			in = fd[0];
		}
		cmd = cmd->next;
	}
	wait_all(tmp);
	printf("test end\n");
}
