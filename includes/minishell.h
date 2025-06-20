#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "colors.h"
# include "memory.h"
# include "structs.h"
# include <stdio.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# define CWD_BUFFER	128
# define NUM_BUILTINS 	2


typedef struct s_redirect
{
	char				*args[2];
	struct s_redirect	*next;
}	t_redirect;


typedef struct s_cmd
{
	char			**args;
	int				redirect_in;
	int				redirect_out;
	t_redirect		*redirect;
	struct s_cmd	*next;
}	t_cmd;

/***************************
DEBUG ---------
****************************/

void	print_tokens(char **tokens);
void	print_cmd(t_cmdtbl *cmd);

#endif
