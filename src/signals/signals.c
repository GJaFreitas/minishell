#include "signals.h"

extern int	g_sig;

void	__sigint_h(int code)
{
	(void)code;
}

void	signals(void)
{
	signal(SIGINT, __sigint_h);
}
