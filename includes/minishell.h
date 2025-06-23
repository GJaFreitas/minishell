#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "colors.h"
# include "memory.h"
# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include <stdio.h>
# include <stdarg.h>
# include <stddef.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>

# define CWD_BUFFER	128
# define NUM_BUILTINS 	2


typedef struct s_redirect
{
	char				*args[2];
	struct s_redirect	*next;
}	t_redirect;


typedef struct s_cmd
{
	int				pid;
	char			**args;
	int				redirect_in;
	int				redirect_out;
	t_redirect		*redirect;
	struct s_cmd	*next;
}	t_cmd;

// Display prompt and parse the line given by the user
t_cmdtbl	*prompt(t_cmdtbl *cmd);

// Returns the next number divisible by 8
unsigned int	next_div_8(unsigned int n);

void	refresh_cmd(t_cmdtbl *cmd);

// EXEC ***********************************

void	ft_exec_all(t_cmd *cmd, char **env);


/***************************
DEBUG ---------
****************************/

void	print_tokens(char **tokens);
void	print_cmd(t_cmd *cmd);

#endif
