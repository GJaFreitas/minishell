#include "parser.h"

int	is_pipe(char *token)
{
	return (*token == '|');
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
}
