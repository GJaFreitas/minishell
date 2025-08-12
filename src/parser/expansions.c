#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <stdint.h>
#include <stdlib.h>

int	is_env_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*__assemble(char *tok, t_expansion_list *list, int size)
{
	t_expansion_list	*cur;
	char	*new;
	int	i;
	int	j;

	i = 0;
	cur = list;
	new = malloc(size + 1);
	while (cur)
	{
		j = 0;
		while (cur->expansion && cur->expansion[j])
			new[i++] = cur->expansion[j++];
		cur = cur->next;
	}
	new[i] = 0;
	return (new);
}

int	expansion_list_size(t_expansion_list *expansions)
{
	t_expansion_list	*cur;
	int	size;

	cur = expansions;
	size = 0;
	while (cur)
	{
		size += ft_strlen(cur->expansion);
		cur = cur->next;
	}
	return (size);
}

char	*__get_expansion(char *tok, char **env)
{
	int	i;
	int	j;

	if (!*tok)
		return (NULL);
	i = 0;
	while (tok[i] && is_env_char(tok[i]))
		i++;
	j = 0;
	while (env[j])
	{
		if (!ft_strncmp(tok, env[j], i) && env[j][i] == '=')
			break ;
		j++;
	}
	if (!env[j])
		return (NULL);
	i = 0;
	while (env[j][i] != '=')
		i++;
	return (&env[j][i + 1]);
}

int	get_expansion_size(char *tok)
{
	int	i;

	i = 0;
	i++;
	while (tok[i] && is_env_char(tok[i]))
		i++;
	return (i);
}

t_expansion_list	*next_expansion(t_expansion_list *list)
{
	list->next = malloc(sizeof(t_expansion_list));
	return (list->next);
}

char	*copy_until_expansion(char *tok)
{
	char	*temp;

	temp = ft_strchr(tok, '$');
	if (temp)
		return (ft_strndup(tok, (uintptr_t)temp - (uintptr_t)tok));
	return (ft_strdup(tok));
}

// Genuinely evil ass function
t_expansion_list	*get_all_expansions(char *tok, char **env)
{
	t_expansion_list	*list;
	t_expansion_list	*cur;
	int	expansion_flag;

	list = malloc(sizeof(t_expansion_list));
	cur = list;
	while (*tok)
	{
		expansion_flag = (tok[0] == '$');
		if (expansion_flag)
			expansion_flag = 0;
		else
		{
			cur->expansion = copy_until_expansion(tok);
			cur = next_expansion(cur);
			while (*tok && *tok != '$')
				tok++;
		}
		cur->expansion = __get_expansion(tok + 1, env);
		cur = next_expansion(cur);
		tok += get_expansion_size(tok);
	}
	return (list);
}

char	*__expand_token(char *tok, char **env)
{
	char	*new_tok;
	t_expansion_list	*expansions;
	int	i;

	i = 0;
	while (tok[i] && tok[i] != '$')
		i++;
	if (!(tok[i] == '$'))
		return (tok);
	expansions = get_all_expansions(tok, env);
	new_tok = __assemble(tok, expansions, expansion_list_size(expansions));
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
	int	i;

	i = 0;
	while (tokens[i])
	{
		tokens[i] = __expand_token(tokens[i], env);
		i++;
	}
}
