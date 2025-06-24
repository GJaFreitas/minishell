#ifndef PARSER_H
# define PARSER_H

# define REDIRECT	"<>"

# include "minishell.h"

t_cmd	*parser(char **tokens, char **env);


t_cmd	*assign_cmds(char **tokens, char **env);
char	*path_search(char *token, char **env);
int	is_pipe(char *token);


// Utils ------------------
void	free_tokens(char **tokens);
// Para chamar no exec ou na main depois
void	free_cmds(t_cmd *cmds);
// ------------------



/*********************
Parser debugging
*********************/
void	parser_debug(char **tokens);

#endif
