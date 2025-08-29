#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>

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

// @TODO: Handle de sinais
int	heredoc(char *delimiter, char **cmd_args)
{
	int				fd[2];

	if (cmd_args[1] != 0)
		return (-1);
	if (pipe(fd) == -1)
		return (perror("Pipe:"), -1);
	get_lines(fd[1], delimiter);
	return (fd[0]);
}
