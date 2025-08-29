#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

void	get_lines(int fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!ft_strcmp(delimiter, line))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
}

int	wait_hdoc(int pid)
{
	int	sig;
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, __sigint_h);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT && write(1, "\n", 1))
			return (-1);
	}
	if (WIFSIGNALED(status))
		return (sig + 128);
	return (1);
}

int	heredoc(char *delimiter, int pipefd[2])
{
	int	pid;

	if (pipe(pipefd) == -1)
		return (perror("Pipe:"), -1);
	pid = fork();
	if (pid == 0)
	{
		if (dup2(pipefd[1], STDIN_FILENO) == -1)
			perror("dup2 hdoc:");
		get_lines(STDIN_FILENO, delimiter);
		free(delimiter);
		return (0);
	}
	wait_hdoc(pid);
	close(pipefd[1]);
	return (pipefd[0]);
}
