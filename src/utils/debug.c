/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 18:43:31 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(char *const *tokens)
{
	int	i;

	i = 0;
	while (*tokens)
	{
		printf("%d - %s\n", i++, *tokens);
		tokens++;
	}
}

void	print_one_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("Builtin: %d\n", cmd->builtin);
	printf("Next exists: %d\n", (cmd->next != NULL));
	while (cmd->args[i])
	{
		printf("%i - %s\n", i, cmd->args[i]);
		i++;
	}
	printf("redirections: in: %d, out: %d \n", cmd->redirect_in,
		cmd->redirect_out);
	printf("\n\n");
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
			printf("%i - %s\n", i, cmd->args[i]);
			i++;
		}
		printf("redirections: in: %d, out: %d \n", cmd->redirect_in,
			cmd->redirect_out);
		printf("Builtin: %d\n", cmd->builtin);
		cmd = cmd->next;
	}
}

void	parser_debug(char **tokens)
{
	printf("--- Tokens received ---\n");
	print_tokens(tokens);
	printf("-----------------------\n");
	printf("\n");
	printf("--- Command created ---\n");
	printf("-----------------------\n");
	printf("\n");
}
