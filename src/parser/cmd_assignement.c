#include "libft.h"
#include "minishell.h"
#include "parser.h"

static t_cmd	*__init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(struct s_cmd));
	cmd->redirect_in = -1;
	cmd->redirect_out = -1;
	return (cmd);
}

static t_redirect	*__redirect(t_redirect *redir, char **tokens)
{
	t_redirect	*cur;

	if (!redir)
	{
		redir = ft_calloc(1, sizeof(struct s_redirect));
		redir->args[0] = ft_strdup(tokens[0]);
		redir->args[1] = ft_strdup(tokens[1]);
	}
	else
	{
		cur = redir;
		while (cur->next)
			cur = cur->next;
		cur->next = ft_calloc(1, sizeof(struct s_redirect));
		cur = cur->next;
		cur->args[0] = ft_strdup(tokens[0]);
		cur->args[1] = ft_strdup(tokens[1]);
	}
	return (redir);
}

static int	__assign_command(t_cmd *cmd, char **tokens, char **env)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_pipe(tokens[i]))
			return (i + 1);
		else if (ft_strchr(REDIRECT, tokens[i][0]))
			cmd->redirect = __redirect(cmd->redirect, &tokens[i++]);
		else if (i == 0)
				cmd->args[i] = path_search(tokens[i], env);
		else
				cmd->args[i] = ft_strdup(tokens[i]);
		i++;
	}
	return (i);
}

int	__arg_count(char **tokens)
{
	int	i;

	i = 1;
	while (*tokens)
	{
		if (is_pipe(*tokens))
			return (i);
		tokens++;
		i++;
	}
	return (i);
}

t_cmd	*assign_cmds(char **tokens, char **env)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = __init_cmd();
	current = cmds;
	while (*tokens)
	{
		current->args = ft_calloc(__arg_count(tokens) + 1, sizeof(char *));
		tokens += __assign_command(current, tokens, env);
		if (*tokens)
		{
			current->next = __init_cmd();
			current = current->next;
		}
	}
	return (cmds);
}
