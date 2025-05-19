#include "minishell.h"

char	**tokenize(const char *line)
{
	char	**tokens;

	tokens = ft_split(line);
	if (!tokens)
		perror("Couldnt tokenize string\n");
	return (tokens);
}

void	free_tokens(char **tokens)
{
	uint	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
