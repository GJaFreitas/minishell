#ifndef PARSER_H
# define PARSER_H

# define REDIRECT	"<>"
# define PIPE 		"|"
# define QUOTES		"\"\'"

# include "structs.h"

void	parser(t_cmdtbl *cmd, char ***tokens);

int	is_pipe(char *token);

int	__options(t_simplecmd *cmd, char *token);
int	__redirections(t_simplecmd *cmd, char **tokens);
int	__args(t_simplecmd *cmd, char *tokens);

void	assign_cmds(t_simplecmd **cmdarray, char **tokens, t_uint count);

void	token_merge(char ***tokens);
void	free_tokens(char **tokens);

#endif
