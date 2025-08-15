#include "minishell.h"

extern pid_t	g_sig;

void	__sigint_h(int code)
{
	(void)code;
	//@TODO: Get this to actually work
	write(0, "\n", 1);
	return ;
}

void	__sigquit_h(int code)
{
	(void)code;
	//@TODO: Use isatty() to get CTRL-\ working
	g_sig = SIGQUIT;
}

void	signals(void)
{
	signal(SIGINT, __sigint_h);
	signal(SIGQUIT, __sigquit_h);
}
