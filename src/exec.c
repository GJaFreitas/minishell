#include "minishell.h"

void	exec_tokens(char **tok)
{
	while (*tok)
	{
		exec_builtins(*tok, tok + 1);
		tok++;
	}
}
