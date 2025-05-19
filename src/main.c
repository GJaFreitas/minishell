#include "minishell.h"

static void	__shell_delimiter(void);
char		*prompt(char **buf);

int	main(int argc, char **argv)
{
	char	*line;
	char	**tokens;

	__shell_delimiter();
	(void)argc;
	(void)argv;
	while (prompt(&line))
	{
		if (!line)
			continue ;
		tokens = tokenize(line);
		exec_tokens(tokens);
		free_tokens(tokens);
		free(line);
	}
	__shell_delimiter();
	return (0);
}

static void	__shell_delimiter(void)
{
	ft_printf(ANSI_BOLD"\n\n----- SHELL DELIMITER -----\n\n\n"
ANSI_RESET);
}

// Display prompt and read the next line given to it
char	*prompt(char **buf)
{
	char	cwd[CWD_BUFFER];

	*buf = NULL;
	if (!getcwd(cwd, CWD_BUFFER))
		perror("getcwd() error\n");
	if (feof(stdin))
		ft_printf("[EOF]");
	ft_printf("%s » ", cwd);
	*buf = get_next_line(0);
	return (*buf);
}

// void	print_tokens(char **tok)
// {
// 	while (*tok)
// 	{
// 		ft_printf("%s\n", *tok);
// 		tok++;
// 	}
// }
