/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:02:16 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/07 18:05:36 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(char *const *tokens)
{
	int	i;

	i = 0;
	while (*tokens)
	{
		ft_printf("%d - %s\n", i++, *tokens);
		tokens++;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			ft_printf("%i - %s\n", i, cmd->args[i]);
			i++;
		}
		ft_printf("redrections flag == in %d, out %d \n",
			cmd->redirect_in, cmd->redirect_out);
		cmd = cmd->next;
	}
}

void	parser_debug(char **tokens)
{
	ft_printf("--- Tokens received ---\n");
	print_tokens(tokens);
	ft_printf("-----------------------\n");
	ft_printf("\n");
	ft_printf("--- Command created ---\n");
	ft_printf("-----------------------\n");
	ft_printf("\n");
}
