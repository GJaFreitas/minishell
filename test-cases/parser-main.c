#include "lexer.h"
#include "parser.h"
#include "minishell.h"

void	print_parser_results(t_cmd *cmds)
{
	int	i = 0;
	t_redirect	*cur;
	while (cmds)
	{
		printf("CMD %d:\n", i++);
		printf("ARGS:\n");
		print_tokens(cmds->args);
		printf("REDIRECTIONS:\n");
		cur = cmds->redirect;
		while (cur)
		{
			print_tokens(cur->args);
			cur = cur->next;
		}
		cmds = cmds->next;
	}
}

// Display prompt and read the next line given to it
void	prompt()
{
	t_cmd *cmds = parser(lexer(get_next_line(0)));
	print_parser_results(cmds);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	prompt();
	return (0);
}
