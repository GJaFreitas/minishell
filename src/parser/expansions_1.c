/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:05:02 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/09/05 19:08:34 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

char	*copy_until_expansion(char *tok)
{
	char	*temp;

	temp = ft_strchr(tok, '$');
	if (temp)
		return (ft_strndup(tok, (uintptr_t)temp - (uintptr_t)tok));
	return (ft_strdup(tok));
}

// Genuinely evil ass function
t_string_list	*get_all_expansions(char *tok, char **env, int exit)
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
			cur->allocd = 1;
			cur = next_expansion(cur);
			while (*tok && *tok != '$')
				tok++;
		}
		if (*tok && tok[1] == '?')
			(void)((cur->allocd = 1) && (cur->expansion = ft_itoa(exit)));
		else if (*tok)
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
		if (cur->allocd)
			free(cur->expansion);
		cur = cur->next;
		free(prev);
	}
}

char	*__expand_token(char *tok, char **env, int exit)
{
	char			*new_tok;
	t_string_list	*expansions;
	int				i;

	i = 0;
	while (tok[i] && tok[i] != '$')
		i++;
	if (tok[i] != '$')
		return (tok);
	expansions = get_all_expansions(tok, env, exit);
	new_tok = __assemble(expansions, expansion_list_size(expansions));
	free_list(expansions);
	free(tok);
	return (new_tok);
}

void	expansions(char **tokens, char **env, int exit)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '\'')
			i++;
		if (!tokens[i])
			break ;
		tokens[i] = __expand_token(tokens[i], env, exit);
		i++;
	}
}
