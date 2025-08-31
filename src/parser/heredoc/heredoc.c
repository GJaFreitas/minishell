/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/08/31 18:28:25 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int	norm_nao_gosta;

static void	__sigint_heredoc(int code)
{
	(void)code;
	g_sig = SIGINT;
	rl_done = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
}

int	get_lines(int fd, const char *delimiter, char **env)
{
	char	*line[2];
	int		line_n;

	norm_nao_gosta = fd;
	signal(SIGINT, __sigint_heredoc);
	line_n = 0;
	line[1] = NULL;
	while (1)
	{
		line_n++;
		line[0] = readline("> ");
		if (!ft_strcmp(delimiter, line[0]) || !line[0] || g_sig)
			break ;
		expansions(line, env, 0);
		ft_fprintf(fd, "%s\n", line[0]);
		free(line[0]);
	}
	if (!line[0])
		return (line_n | HDOC_EOF);
	free(line[0]);
	signal(SIGINT, __sigint_h);
	if (g_sig)
		return (-2);
	return (0);
}

int	heredoc(char *delimiter, int pipefd[2], char **env)
{
	pid_t	pid;
    int		status;

    if (pipe(pipefd) == -1)
        return (perror("Pipe:"), -1);
    pid = fork();
    if (pid == -1)
        return (perror("Fork:"), close(pipefd[0]), close(pipefd[1]), -1);
    if (pid == 0)
    {
        close(pipefd[0]);
        signal(SIGINT, SIG_DFL);
        get_lines(pipefd[1], delimiter, env);
        close(pipefd[1]);
        	exit(g_sig);
    }
    close(pipefd[1]);
    waitpid(pid, &status, 0);
    return (pipefd[0]);
	// todo memory duplicate 
}

// Substitutes delimiter token for fd of HEREDOC pipe
void	handle_heredoc(char **tokens, char **env)
{
	int	read_pipe_fd;
	int	pipefd[2];

	if (!tokens[1])
		return (ft_fprintf(2, "Please give a delimiter\n"), (void)0);
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
