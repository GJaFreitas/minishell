#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "minishell.h"

char **_new_env(void)
{
	char	**env;

	env = calloc(sizeof(char *), 10);
	env[0] = ft_strdup("HOME=/home/bag");
	env[1] = ft_strdup("A=variavel");
	env[2] = ft_strdup("C=variavel");
	env[3] = ft_strdup("B=variavel");
	return (env);
}

static void	shell_loop(t_env *env)
{
	t_cmd	*cmd;
	while (1)
	{
		cmd = parser(lexer(get_next_line(0)), env);
		ft_export(cmd->args, env);
		printf("\n ---- \n");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_t;
	(void)argc;
	(void)argv;
	(void)env;
	env_t = init_env(_new_env());
	shell_loop(env_t);
	return (0);
}
