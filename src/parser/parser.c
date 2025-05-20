#include "minishell.h"
#include "parser.h"
#include "structs.h"

// Transverses the tokens and finds out how many commands there are
t_simplecmd	**alloc_cmd_array(char **tokens, int *c)
{
	t_simplecmd	**cmd_array;
	unsigned int		count;
	unsigned int		i;

	count = 1;
	while (*tokens)
	{
		if ((*tokens)[0] == '|')
			count++;
		tokens++;
	}
	cmd_array = ft_calloc(count + 1, sizeof(t_simplecmd *));
	i = 0;
	while (i < count)
		cmd_array[i++] = ft_calloc(1, sizeof(t_simplecmd));
	*c = count;
	return (cmd_array);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
}

void	parser(t_cmdtbl *cmd, char **tokens)
{
	t_simplecmd	**cmdarray;
	int		cmd_count;

	cmdarray = alloc_cmd_array(tokens, &cmd_count);
	cmd->num_cmds = cmd_count;
	// expansions(tokens);
	token_merge(&tokens); // Merge the tokens between " or ' into one
	assign_cmds(cmdarray, tokens, cmd_count);
	cmd->cmds = cmdarray;
	free_tokens(tokens);
	free(tokens);
}
