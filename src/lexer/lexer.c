/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:22 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 15:44:10 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include <stddef.h>
#include <stdio.h>

char	**__tokenize(char *str);
static char	*__prepare_tokenize(char *s);
void	__remove_newline(char *line);
void	__expansions(char **line, size_t mem);

/*******************************

ls -la a* |grep me > outfile

cat -e <infile | grep a

ls dir|grep a

********************************/

char	**lexer(char *line)
{
	int	i;
	char	**toks;
	char	*tokenizable;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (free(line), NULL);
	tokenizable = __prepare_tokenize(line);
	toks = __tokenize(tokenizable);
	free(tokenizable);
	return (toks);
}

int	meta_char_handler(char *s, int i, char *str)
{
	int	count;

	count = 0;
	if (i-1 >= 0 && s[i-1] != ' ' && !special_char(s[i-1]))
		str[count++] = ' ';
	str[count++] = s[i];
	if (s[i+1] != ' ' && !special_char(s[i+1]))
		str[count++] = ' ';
	return (count);
}

static char	*__prepare_tokenize(char *s)
{
	unsigned int	i;
	unsigned int	j;
	char		*str;

	i = 0;
	j = 0;
	str = ft_calloc(1, (ft_strlen(s) * 2) + 1);
	while (s[i] && s[i + 1])
	{
		if (special_char(s[i]))
			j += meta_char_handler(s, i, str + j);
		else
			str[j++] = s[i];
		i++;
	}
	str[j++] = s[i];
	str[j] = 0;
	return (str);
}
