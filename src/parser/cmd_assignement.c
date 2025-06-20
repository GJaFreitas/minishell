#include "libft.h"
#include "parser.h"

static t_cmd	*__init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(struct s_cmd));
	cmd->redirect_in = -1;
	cmd->redirect_out = -1;
	return (cmd);
}

static t_redirect	*__redirect(t_redirect *redir, char *token)
{
	t_redirect	*cur;

	if (!redir)
	{
		redir = ft_calloc(1, sizeof(struct s_cmd));
		ft_strlcpy(redir->args, token, 2);
	}
	else
	{
		cur = redir;
		while (cur->next)
			cur = cur->next;
		cur->next = ft_calloc(1, sizeof(struct s_cmd));
		cur = cur->next;
		ft_strlcpy(cur->args, token, 2);
	}
	return (redir);
}

static int	__assign_command(t_cmd *cmd, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_pipe(tokens[i]))
			return (i + 1);
		else if (ft_strchr(REDIRECT, tokens[i][0]))
			cmd->redirect = __redirect(cmd->redirect, tokens[i]);
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

t_cmd	*assign_cmds(char **tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = __init_cmd();
	current = cmds;
	while (*tokens)
	{
		current->args = ft_calloc(__arg_count(tokens) + 1, sizeof(char *));
		tokens += __assign_command(current, tokens);
		if (*tokens)
		{
			current->next = __init_cmd();
			current = current->next;
		}
	}
	return (cmds);
}
