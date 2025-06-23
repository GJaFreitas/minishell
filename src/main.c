#include "minishell.h"
#include "structs.h"

int	g_sig;

// // Display prompt and read the next line given to it
static t_cmd	*prompt_test()
{
	// ls -la | wc
	t_cmd *cmd1 = ft_calloc(sizeof(t_cmd), 1);

	t_cmd *cmd2 = ft_calloc(sizeof(t_cmd), 1);

	cmd1->redirect_out = open("t.text", O_WRONLY | O_CREAT, 777);
	cmd1->args = ft_calloc(sizeof(char *), 3);
	cmd1->args[0] = ft_strdup("/bin/ls");
	cmd1->args[1] = ft_strdup("-la");
	cmd2->args = ft_calloc(sizeof(char *), 3);
	cmd2->args[0] = ft_strdup("/usr/bin/wc");
	cmd1->next = cmd2;
	return (cmd1);
}

static void	shell_loop(char **env)
{
	t_cmd	*cmd;

	// while (1)
	// {
	cmd = prompt_test();
	ft_exec_all(cmd, env);
	// }
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	// signals();
	shell_loop(env);
	return (0);
}
