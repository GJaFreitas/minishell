#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <fcntl.h>
#include <readline/readline.h>

void	get_lines(int fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(delimiter, line))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
}

void	get_filename(char f[16])
{
	int	fd;
	int	i;

	fd = open("/dev/random", O_RDONLY);
	read(fd, f, 15);
	i = 0;
	while (i < 15)
	{
		if (!ft_isprint(f[i]))
			while (!ft_isprint(f[i]))
				read(fd, &f[i], 1);
		i++;
	}
	f[21] = 0;
}

// @TODO: Handle de sinais
int	heredoc(char *delimiter, char **cmd_args)
{
	char			filename[32];
	int				fd;

	if (cmd_args[1] != 0)
		return (-1);
	ft_strlcpy(filename, "/tmp/", 6);
	get_filename(&filename[5]);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	get_lines(fd, delimiter);
	return (fd);
}
