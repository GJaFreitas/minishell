#include "minishell.h"

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (*tokens)
	{
		printf("%d - %s\n", i++, *tokens);
		tokens++;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int i = 0;
	while (cmd)
	{
	i = 0;
	while(cmd->args[i])
	{
		printf("%i - %s\n", i, cmd->args[i]);
		i++;
	}
	printf("=========================\n");
	cmd = cmd->next;
	}
}

void	parser_debug(char **tokens)
{
	//printf("--- Tokens received ---\n");
	//print_tokens(tokens);
	//printf("-----------------------\n");
	//printf("\n");
	//printf("--- Command created ---\n");
	//print_cmd(cmd);
	//printf("-----------------------\n");
	//printf("\n");
}

