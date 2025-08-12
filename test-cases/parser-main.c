#include "lexer.h"
#include "parser.h"
#include "minishell.h"

void	print_output(char **args)
{
	while (*args)
	{
		printf("%s ", *args);
		args++;
	}
	printf("\n");
}

void	prompt(t_env *env)
{
	t_cmd *cmds = parser(lexer(get_next_line(0)), env);
	print_output(cmds->args);
	free_cmds(cmds);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_t;
	(void)argc;
	(void)argv;
	env_t = init_env(env);
	prompt(env_t);
	return (0);
}
