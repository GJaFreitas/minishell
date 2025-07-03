#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

struct s_cmd;
typedef struct s_cmd t_cmd;

int setup_redirections(t_cmd *cmd);
void ft_exec(t_cmd *cmd, int in, int out, char **env);
void ft_exec_all(t_cmd *cmd, char **env);

#endif