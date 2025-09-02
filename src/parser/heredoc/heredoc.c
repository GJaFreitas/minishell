/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/09/01 12:12:07 by bag              ###   ########.fr       */
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

int	get_lines(int fd, const char *delimiter, char **env)
{
	char	*line[2];
	int		line_n;

	line_n = 0;
	line[1] = NULL;
	while (1)
	{
		line_n++;
		line[0] = readline("> ");
		if (!ft_strcmp(delimiter, line[0]) || !line[0])
			break ;
		expansions(line, env, 0);
		ft_fprintf(fd, "%s\n", line[0]);
		free(line[0]);
	}
	if (!line[0])
		return (line_n | HDOC_EOF);
	free(line[0]);
	if (g_sig)
		return (-2);
	return (0);
}

int	heredoc(char *delimiter, char **env)
{
	pid_t	pid;
	int		fd;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (perror("Fork:"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		fd = open("/tmp/hdoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		get_lines(fd, delimiter, env);
		close(fd);
		exit(g_sig);
	}
	else
	{
		waitpid(pid, &g_sig, 0);
		write(1, "\n", 1);
		signal(SIGINT, __sigint_h);
	}
	if (g_sig == 0)
		return (open("/tmp/hdoc", O_RDONLY));
	return (-1);
}

// Substitutes delimiter token for fd of HEREDOC pipe
void	handle_heredoc(char **tokens, char **env)
{
	int	fd;

	if (!tokens[1])
		return (ft_fprintf(2, "Please give a delimiter\n"), (void)0);
	fd = heredoc(tokens[1], env);
	free(tokens[1]);
	tokens[1] = ft_itoa(fd);
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
