#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"

int	is_env_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*__assemble(char *first, char *second, char *third)
{
	char	*new;
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (first[i] != '$')
		i++;
	while (*second != '=')
		second++;
	new = malloc(i + ft_strlen(++second) + ft_strlen(third));
	while (i != ++j)
		new[j] = first[j];
	while (*second)
		new[j++] = *second++;
	while (*third)
		new[j++] = *third++;
	return (new);
}

char	*__expand_token(char *tok, char **env, int len)
{
	int	i;
	char	*expanded;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(tok, env[i], len) && env[i][len] == '=')
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	expanded = ft_strdup(env[i]);
	return (expanded);
}

char	*__expand_quote(char *tok, char **env)
{
	char	*expand;
	char	*rest;
	char	*new_tok;
	int	i;

	i = 0;
	new_tok = tok;
	expand = 0;
	while (*tok)
	{
		if (*tok == '$')
		{
			tok++;
			while (tok[i] && is_env_char(tok[i]))
				i++;
			expand = __expand_token(tok, env, i);
			rest = &tok[i];
		}
		tok++;
	}
	if (!expand)
		return (tok);
	new_tok = __assemble(new_tok, expand, rest);
	return (new_tok);
}

void	expansions(char **tokens, char **env)
{
	char	*temp;
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '\"')
			temp = __expand_quote(tokens[i], env);
		else if (tokens[i][0] == '$')
			temp = __expand_token(tokens[i], env, 0);
		if (temp && temp != tokens[i])
		{
			free(tokens[i]);
			tokens[i] = temp;
		}
		i++;
	}
}
