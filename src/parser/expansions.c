#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

int	is_env_char(int c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

char	*__assemble(char *tok, t_string_list *list, int size)
{
	t_string_list	*cur;
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
		if (cur->allocd)
			free(cur->expansion);
		cur = cur->next;
	}
	new[i] = 0;
	return (new);
}

int	expansion_list_size(t_string_list *expansions)
{
	t_string_list	*cur;
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

t_string_list	*next_expansion(t_string_list *list)
{
	list->next = ft_calloc(1, sizeof(t_string_list));
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
t_string_list	*get_all_expansions(char *tok, char **env, u_char exit)
{
	t_string_list	*list;
	t_string_list	*cur;

	list = ft_calloc(1, sizeof(t_string_list));
	cur = list;
	while (*tok)
	{
		if (tok[0] != '$')
		{
			cur->expansion = copy_until_expansion(tok);
			cur = next_expansion(cur);
			while (*tok && *tok != '$')
				tok++;
		}
		if (tok[1] == '?')
			(cur->allocd = 1) && (cur->expansion = ft_itoa(exit));
		else
			cur->expansion = __get_expansion(tok + 1, env);
		cur = next_expansion(cur);
		tok += get_expansion_size(tok);
	}
	return (list);
}

void	free_list(t_string_list *l)
{
	t_string_list	*cur;
	t_string_list	*prev;

	cur = l;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev);
	}
}

char	*__expand_token(char *tok, char **env, u_char exit)
{
	char	*new_tok;
	t_string_list	*expansions;
	int	i;

	i = 0;
	while (tok[i] && tok[i] != '$')
		i++;
	if (!(tok[i] == '$'))
		return (tok);
	expansions = get_all_expansions(tok, env, exit);
	new_tok = __assemble(tok, expansions, expansion_list_size(expansions));
	free_list(expansions);
	free(tok);
	return (new_tok);
}

void	expansions(char **tokens, char **env, u_char exit)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		tokens[i] = __expand_token(tokens[i], env, exit);
		i++;
	}
}
