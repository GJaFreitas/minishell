#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"

int	is_env_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

int	__total_size(char *first, char *second, char *third)
{
	int	size;

	size = 0;
	while (first[size] != '$')
		size++;
	while (*second && *second != '=')
		second++;
	size += ft_strlen(second);
	size += ft_strlen(third);
	return (size + 4);
}

char	*__assemble(char *first, char *second, char *third)
{
	char	*new;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new = malloc(__total_size(first, second, third));
	while (first[j] != '$')
		new[i++] = first[j++];
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
	char	*temp;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(tok, env[i], len) && env[i][len] == '=')
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	temp = env[i];
	while (*temp++ != '=');
	expanded = ft_strdup(temp);
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

/*
*  @TODO: Add multiple expansions support
*
*  echo $HOME$HOME
*  echo "$HOME is at $HOME"
*
*  and other cases
*/
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
			temp = __expand_token(&tokens[i][1], env, ft_strlen(tokens[i]) - 1);
		if (temp && temp != tokens[i])
		{
			free(tokens[i]);
			tokens[i] = temp;
		}
		i++;
	}
}
