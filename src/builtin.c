#include "minishell.h"

static void	__placebo(char **args)
{
	(void)args;
}

static t_builtin	*builtin(int i)
{
	static t_builtin	b[NUM_BUILTINS] = {\
	{ft_echo}, {__placebo} };
	if (i)
		return (&b[i - 1]);
	else
		return (&b[NUM_BUILTINS - 1]);
}

int	ft_isbuiltin(const char *str)
{
	static char	*builtins[3] = {\
	"echo", "env", "exit" };
	unsigned int	i;

	i = 0;
	while (i < 3)
		if (!ft_strncmp(str, builtins[i++], 4))
			return (i);
	return (0);
}

// If f isnt a builtin then the placeboo function will run, doing a whole
// lot of nothing. If f is a builtin then the correct builtin will get called
// f is the current token and tok is the list of tokens after that
void	exec_builtins(const char *f, char **tok)
{
	builtin(ft_isbuiltin(f))->foo(tok);
}
