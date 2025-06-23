#ifndef PARSER_H
# define PARSER_H

# define REDIRECT	"<>"

# include "minishell.h"

t_cmd	*parser(char **tokens);
t_cmd	*assign_cmds(char **tokens);



int	is_pipe(char *token);
void	free_tokens(char **tokens);

/*********************
Parser debugging
*********************/
void	parser_debug(char **tokens);

#endif
