/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/09/06 16:29:34 by gjacome-         ###   ########.fr       */
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

void	__hdoc_sigint(int code)
{
	t_hdoc	*norm;

	(void)code;
	norm = hdoc_norm(NULL);
	close(norm->fd);
	norm->fd = open("/tmp/hdoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	(free_env(norm->env), free_tokens(norm->delimiter));
	(free(norm->delimiter), close(norm->fd));
	exit(SIGINT);
}

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
		return (free(line[0]), line_n | (1 << 31));
	free(line[0]);
	if (g_sig)
		return (-2);
	return (0);
}

int	heredoc(char **delimiter, t_env *env)
{
	pid_t	pid;
	int		fd;

	(signal(SIGINT, SIG_IGN), pid = fork());
	if (pid == 0)
	{
		signal(SIGINT, __hdoc_sigint);
		fd = open("/tmp/hdoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		hdoc_norm(&(struct s_hdoc){env, delimiter, fd});
		pid = get_lines(fd, delimiter[2], env_to_array(env));
		if ((pid >> 31) & 1)
		{
			ft_fprintf(2, HDOC_ERROR1 HDOC_ERROR2, pid << 1 >> 1, delimiter[2]);
			close(fd);
			fd = open("/tmp/hdoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		(free_env(env), free_tokens(delimiter), free(delimiter), close(fd));
		exit(g_sig);
	}
	else
		(waitpid(pid, &g_sig, 0), write(1, "\n", 1), signal(SIGINT,
				__sigint_h));
	if (g_sig == 0)
		return (open("/tmp/hdoc", O_RDONLY));
	return (-1);
}

// Substitutes delimiter token for fd of HEREDOC pipe
void	handle_heredoc(char **tokens, t_env *env)
{
	int	fd;

	if (!tokens[2])
		return (ft_fprintf(2, "Please give a delimiter\n"), (void)0);
	fd = heredoc(tokens, env);
	free(tokens[2]);
	tokens[2] = ft_itoa(fd);
}

void	heredocs(char **tokens, t_env *env)
{
	int	i;

	g_sig = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i] && !ft_strcmp(tokens[i], "<<"))
			handle_heredoc(tokens, env);
		if (!tokens[i])
			break ;
		i++;
	}
}
