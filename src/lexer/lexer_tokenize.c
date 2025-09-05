/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:22 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 18:43:31 by bag              ###   ########.fr       */
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

	tok = malloc(sizeof(char *) * (__count_tokens(str) + 1));
	if (!__create_tokens(str, tok))
		free_tokens(tok);
	return (tok);
}

// If temp is a quote temp will be incremented until the next quote
static int	__next_quote(char *temp)
{
	int	i;

	i = 1;
	if (!ft_strchr(QUOTES, *temp))
		return (0);
	while (temp[i] && !ft_strchr(QUOTES, temp[i]))
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
