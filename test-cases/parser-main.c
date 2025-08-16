#include "lexer.h"
#include "parser.h"
#include "minishell.h"

void	print_output(t_cmd *cmd)
{
	printf("Is Builtin: %d\n", cmd->builtin);
	printf("Args: \n");
	while (*cmd->args)
	{
		printf("%s ", *cmd->args);
		cmd->args++;
	}
	printf("\n");
}

void	prompt(t_env *env)
{
	t_cmd *cmds = parser(lexer(get_next_line(0)), env);
	while (cmds)
	{
		print_output(cmds);
		cmds = cmds->next;
	}
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
