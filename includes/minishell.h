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
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# define CWD_BUFFER	128
# define NUM_BUILTINS 	2

typedef struct s_builtin
{
	void	(*foo)(char **args);
}	t_builtin;

int				ft_isbuiltin(const char *str);
void			exec_builtins(const char *f, char **tok);
void			ft_echo(char **args);


// Display prompt and parse the line given by the user
t_cmdtbl	*prompt(t_cmdtbl *cmd);

// Returns the next number divisible by 8
unsigned int	next_div_8(unsigned int n);

void	refresh_cmd(t_cmdtbl *cmd);



/***************************
DEBUG ---------
****************************/

void	print_tokens(char **tokens);
void	print_cmd(t_cmdtbl *cmd);

#endif
