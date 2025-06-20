#include "minishell.h"
#include "parser.h"

t_cmd	*parser(char **tokens)
{
	t_cmd		*cmds;

	// expansions(tokens);

	//@Remove
	#ifdef DEBUG
	parser_debug(*tokens);
	#endif

	cmds = assign_cmds(tokens);
	free_tokens(tokens);
	free(tokens);
	return (cmds);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
}
