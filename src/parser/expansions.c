/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 19:06:32 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*__assemble(t_string_list *list, int size)
{
	t_string_list	*cur;
	char			*new;
	int				i;
	int				j;

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

int	expansion_list_size(t_string_list *expansions)
{
	t_string_list	*cur;
	int				size;

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
