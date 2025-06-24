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
			printf("1 - %s\n", cur->args[0]);
			printf("2 - %s\n", cur->args[1]);
			cur = cur->next;
			printf("\n");
		}
		cmds = cmds->next;
		printf("\n");
	}
}

void	prompt(char **env)
{
	t_cmd *cmds = parser(lexer(get_next_line(0)), env);
	print_parser_results(cmds);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	prompt(env);
	return (0);
}
