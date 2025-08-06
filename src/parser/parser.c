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

	while (cmds)
	{
		i = 0;
		while (cmds->args[i])
			__rm_quote_arg(cmds->args[i++]);
		cmds = cmds->next;
	}
}

t_cmd	*parser(char **tokens, t_env *env)
{
	t_cmd		*cmds;
	char		**env_expansions;

	if (tokens == NULL)
		return (NULL);
	env_expansions = env_to_array(env);
	expansions(tokens, env_expansions);
	free_env_array(env_expansions);
	cmds = assign_cmds(tokens, env);
	__remove_quotes(cmds);
	free_tokens(tokens);
	free(tokens);
	return (cmds);
}
