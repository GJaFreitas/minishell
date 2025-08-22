#include "minishell.h"
#include <readline/readline.h>

extern pid_t	g_sig;

void	__sigint_h(int code)
{
	(void)code;
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	__sigquit_h(int code)
{
	(void)code;
}

void	signals(void)
{
	signal(SIGINT, __sigint_h);
	signal(SIGQUIT, SIG_IGN);
}
