#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"

static t_redirect	*__redirect(t_redirect *redir, char **tokens, int *i)
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
	*i += 2;
	return (redir);
}

static enum e_builtin	is_builtin(enum e_builtin *cmd, char *token)
{
	static char	*builtins[8] = { "echo", "cd", "pwd", \
		"export", "unset", "env", "exit", NULL};
	int	i;
	int	tokenLen;

	tokenLen = ft_strlen(token);
	i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(token, builtins[i], tokenLen))
		{
			*cmd = i + 1;
			return (1);
		}
		i++;
	}
	*cmd = 0;
	return (0);
}

static int	__assign_command(t_cmd *cmd, char **tokens, char **env)
{
	int	i;
	int	tok_index;

	i = 0;
	tok_index = -1;
	while (tokens[++tok_index])
	{
		if (is_pipe(tokens[tok_index]))
			return (tok_index + 1);
		else if (tokens[tok_index][0] && ft_strchr(REDIRECT, tokens[tok_index][0]))
			cmd->redirect = __redirect(cmd->redirect, &tokens[tok_index++], &i);
		else if (tokens[tok_index][0] && i == 0)
		{
			if (!is_builtin(&cmd->builtin, tokens[tok_index]))
				cmd->args[i++] = path_search(tokens[tok_index], env, &cmd->builtin);
			else
				cmd->args[i++] = ft_strdup(tokens[tok_index]);
		}
		else
			cmd->args[i++] = ft_strdup(tokens[tok_index]);
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
		if (!ft_strchr(REDIRECT, **tokens))
			i++;
		tokens++;
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
