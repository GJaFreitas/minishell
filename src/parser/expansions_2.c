/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:58:57 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/07 17:59:37 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"

void	expansions(char **tokens, char **env)
{
	char	*temp;
	int		i;

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
