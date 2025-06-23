#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "structs.h"

int	g_sig;

// Display prompt and read the next line given to it
t_cmd	*prompt(char **env)
{
	char *line;
	char cwd[CWD_BUFFER];

	if (!getcwd(cwd, CWD_BUFFER))
		perror("getcwd() error\n");
	if (feof(stdin))
		return (ft_printf("exit"), NULL);
	ft_printf("%s » ", cwd);
	line = get_next_line(0);
	if (!line)
		exit(0);
	return (parser(lexer(line), env));
}

static void	shell_loop(char **env)
{
	t_cmd	*cmd;

	while (1)
	{
		cmd = prompt(env);
		ft_exec_all(cmd, env);
	}
	
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	// signals();
	shell_loop(env);
	return (0);
}
