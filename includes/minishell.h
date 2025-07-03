#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "colors.h"
# include "memory.h"
# include "structs.h"
# include <stdio.h>
# include <stdarg.h>
# include <stddef.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>

# define CWD_BUFFER	1024

typedef struct s_redirect
{
	char				*args[2];
	struct s_redirect	*next;
}	t_redirect;

enum e_builtin
{
	NO_BUILTIN = 0,
	CMD_ECHO,
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT,
};

typedef struct s_cmd
{
	int				pid;
	char			**args;
	enum e_builtin		builtin;
	int				redirect_in;
	int				redirect_out;
	t_redirect		*redirect;
	struct s_cmd	*next;
}	t_cmd;

void	ft_exec_all(t_cmd *cmd, char **env);
int	ft_export(char *const argv[], char *const env[]);
/***************************
DEBUG ---------
****************************/

void	print_tokens(char **tokens);
void	print_cmd(t_cmd *cmd);

#endif
