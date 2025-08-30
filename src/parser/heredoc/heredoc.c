#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "signals.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

extern pid_t	g_sig;

static void	__sigint_heredoc(int code)
{
	(void)code;
	g_sig = SIGINT;
	rl_done = 1;
	write(STDIN_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

int	get_lines(int fd, const char *delimiter, char **env)
{
	char	*line;
	int		line_n;

	signal(SIGINT, __sigint_heredoc);
	line_n = 0;
	while (1)
	{
		line_n++;
		line = readline("> ");
		if (!ft_strcmp(delimiter, line) || !line)
			break ;
		expansions(&line, env, 0);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (!line)
		return (line_n | HDOC_EOF);
	if (g_sig)
		return (-2);
	signal(SIGINT, __sigint_h);
	g_sig = 0;
	free(line);
	return (0);
}

int	heredoc(char *delimiter, int pipefd[2], char **env)
{
	volatile int	flag;

	if (pipe(pipefd) == -1)
		return (perror("Pipe:"), -1);
	flag = get_lines(pipefd[1], delimiter, env);
	if ((flag >> 31) & 1)
		printf("bash: warning: here-document at line \
			%d delimited by end-of-file (wanted %s)\n", flag << 1 >> 1, \
			delimiter);
	else if (flag == -2)
		printf("ctrl-c pressed\n");
	close(pipefd[1]);
	return (pipefd[0]);
}

// Substitutes delimiter token for fd of HEREDOC pipe
void	handle_heredoc(char **tokens, char **env)
{
	int	read_pipe_fd;
	int	pipefd[2];

	if (!tokens[1])
		return (printf("Please give a delimiter\n"), (void)0);
	read_pipe_fd = heredoc(tokens[1], pipefd, env);
	free(tokens[1]);
	tokens[1] = ft_itoa(read_pipe_fd);
}

void	heredocs(char **tokens, char **env)
{
	int	i;

	g_sig = 0;
	i = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<<"))
			handle_heredoc(&tokens[i++], env);
		i++;
	}
}
