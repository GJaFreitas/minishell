#ifndef PARSER_H
# define PARSER_H

# define REDIRECT	"<>"
# define PIPE 		"|"

# include "structs.h"

void	assign_cmds(t_simplecmd **cmdarray, char **tokens);

int	is_pipe(char *token);

#endif
