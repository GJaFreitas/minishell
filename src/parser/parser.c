#include "minishell.h"
#include "structs.h"

// Transverses the tokens and finds out how many commands there are
t_simplecmd	**alloc_cmd_array(char **tokens)
{
	t_simplecmd	**cmd_array;
	unsigned int		count;
	unsigned int		i;

	count = 0;
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
	return (cmd_array);
}

void	parser(t_cmdtbl *cmd, char **tokens)
{
	t_simplecmd	**cmdarray;

	cmdarray = alloc_cmd_array(tokens);
	// expansions(tokens);
	// token_merge(tokens); // Merge the tokens between " or ' into one
	// assign_cmds(cmdarray, tokens);
	cmd->cmds = cmdarray;
	// free_tokens(tokens);
}
