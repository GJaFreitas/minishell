#include "lexer.h"
#include "parser.h"
#include "minishell.h"

void	prompt(t_env *env)
{
	t_cmd *cmds = parser(lexer(get_next_line(0)), env);
	ft_cd(cmds->args, env);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_t;
	(void)argc;
	(void)argv;
	env_t = init_env(env);
	while (1)
		prompt(env_t);
	return (0);
}
