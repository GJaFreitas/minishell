#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"

static void	__rm_quote_arg(char *arg)
{
	while (*arg)
	{
		if (ft_strchr(QUOTES, *arg))
			ft_memcpy(arg, arg + 1, ft_strlen(arg + 1) + 1);
		else
			arg++;
	}
}

static void	__remove_quotes(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		while (cmds->args[i])
			__rm_quote_arg(cmds->args[i++]);
		cmds = cmds->next;
	}
}

t_cmd	*parser(char **tokens, char **env)
{
	t_cmd		*cmds;

	if (tokens == NULL)
		return (NULL);
	// expansions(tokens);

	//@Remove
	#ifdef DEBUG
	parser_debug(*tokens);
	#endif

	cmds = assign_cmds(tokens, env);
	__remove_quotes(cmds);
	free_tokens(tokens);
	free(tokens);
	return (cmds);
}
