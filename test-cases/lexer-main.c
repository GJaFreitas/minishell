#include "minishell.h"
#include "structs.h"

void	print_tokens_test(char **tokens)
{
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
}

// Display prompt and read the next line given to it
t_cmdtbl	*prompt(t_cmdtbl *cmd)
{
	char	*line;
	char	**tok;

	line = get_next_line(0);
	tok = lexer(line);
	print_tokens_test(tok);
	return (cmd);
}

static void	shell_loop(void)
{
	t_cmdtbl	cmd;

	while (prompt(&cmd))
	{
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	shell_loop();
	return (0);
}
