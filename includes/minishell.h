#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "colors.h"
# include "memory.h"
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

char			**tokenize(const char *line);
void			free_tokens(char **tokens);
void			exec_tokens(char **tok);

int				ft_isbuiltin(const char *str);
void			exec_builtins(const char *f, char **tok);
void			ft_echo(char **args);

#endif
