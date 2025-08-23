#include "minishell.h"
#include <readline/readline.h>
#include <unistd.h>

extern pid_t	g_sig;

void	__sigint_h(int code)
{
	g_sig = SIGINT;
	write(STDIN_FILENO, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
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
