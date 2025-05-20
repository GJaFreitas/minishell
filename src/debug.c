#include "minishell.h"

void	print_tokens(char **tokens)
{
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
}
