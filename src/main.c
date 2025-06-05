#include "minishell.h"
#include "structs.h"

static void	__shell_delimiter(void);

// Display prompt and read the next line given to it
t_cmdtbl	*prompt(t_cmdtbl *cmd)
{
	char	*line;
	char	**tok;
	char	cwd[CWD_BUFFER];

	if (!getcwd(cwd, CWD_BUFFER))
		perror("getcwd() error\n");
	if (feof(stdin))
		ft_printf("[EOF]");
	ft_printf("%s » ", cwd);
	line = get_next_line(0);
	tok = lexer(line);
	if (tok)
		parser(cmd, &tok);
	return (cmd);
}

static void	shell_loop(void)
{
	t_cmdtbl	cmd;

	while (prompt(&cmd))
	{
		refresh_cmd(&cmd);
	}
}

int	main(int argc, char **argv)
{
	__shell_delimiter();
	(void)argc;
	(void)argv;
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
