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

void	print_cmd(t_cmdtbl *cmd)
{
	if (cmd->cmds[0]->cmd)
		printf("%s\n", cmd->cmds[0]->cmd);
	if (cmd->cmds[0]->opts)
		printf("%s\n", cmd->cmds[0]->opts);
	if (cmd->cmds[0]->args)
		printf("%s\n", cmd->cmds[0]->args);
	if (cmd->cmds[0]->infile)
		printf("%s\n", cmd->cmds[0]->infile);
	if (cmd->cmds[0]->outfile)
		printf("%s\n", cmd->cmds[0]->outfile);
}

void	parser_debug(char **tokens)
{
	printf("--- Tokens received ---\n");
	print_tokens(tokens);
	printf("-----------------------\n");
	printf("\n");
	// printf("--- Command created ---\n");
	// print_cmd(cmd);
	// printf("-----------------------\n");
	printf("\n");
}
