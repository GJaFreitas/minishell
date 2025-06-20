#include "minishell.h"
#include "structs.h"

static void	__shell_delimiter(void);

int	g_sig;

// Display prompt and read the next line given to it
t_cmd	*prompt()
{
	char	*line;
	char	cwd[CWD_BUFFER];

	if (!getcwd(cwd, CWD_BUFFER))
		perror("getcwd() error\n");
	if (feof(stdin))
		return (ft_printf("exit"), NULL);
	ft_printf("%s » ", cwd);
	line = get_next_line(0);
	if (!line)
		exit(0);
	return parser(lexer(line));
}

static void	shell_loop(void)
{
	t_cmd	*cmd;

	while (1)
	{
		cmd = prompt()
		// refresh_cmd(&cmd);
	}
}

int	main(int argc, char **argv, char **env)
{
	__shell_delimiter();
	(void)argc;
	(void)argv;
	(void)env;
	// signals();
	shell_loop();
	__shell_delimiter();
	return (0);
}

static void	__shell_delimiter(void)
{
	ft_printf(ANSI_BOLD"\n\n----- SHELL DELIMITER -----\n\n\n"
ANSI_RESET);
}
