/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:22 by bag               #+#    #+#             */
/*   Updated: 2025/09/06 18:24:48 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "parser.h"

static int	__count_tokens(char *s);
static int	__create_tokens(char *s, char **tok);

char	**__tokenize(char *str)
{
	char	**tok;

	tok = ft_calloc((__count_tokens(str) + 1), sizeof(char *));
	if (!__create_tokens(str, tok))
		free_tokens(tok);
	return (tok);
}

// If temp is a quote temp will be incremented until the next quote
static int	__next_quote(char *temp)
{
	int		i;
	char	cur;

	i = 1;
	if (!ft_strchr(QUOTES, *temp))
		return (0);
	cur = *ft_strchr(QUOTES, *temp);
	while (temp[i] && temp[i] != cur)
		i++;
	return (i);
}

static int	__create_tokens(char *s, char **tok)
{
	char	*temp;

	temp = s;
	while (*temp)
	{
		while (*s && ft_isspace(*s))
			s++;
		temp = s;
		while (*temp && !ft_isspace(*temp))
			temp += __next_quote(temp) + 1;
		if (ft_isspace(*temp) || temp > s)
		{
			*tok = ft_substr(s, 0, temp - s);
			if (*tok == NULL)
				return (0);
			s = temp;
			++tok;
		}
	}
	*tok = NULL;
	return (1);
}

static int	__count_tokens(char *s)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s)
			++word_count;
		while (*s && !ft_isspace(*s))
			++s;
	}
	return (word_count);
}
