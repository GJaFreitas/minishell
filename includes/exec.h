#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

struct s_cmd;
typedef struct s_cmd t_cmd;
struct  s_env;
typedef struct s_env t_env;

int		setup_redirections(t_cmd *cmd);
void	ft_exec(t_cmd *cmd, int in, int out, t_env *env);
void	ft_exec_all(t_cmd *cmd, t_env *env);
int		ft_export_l(char **args, t_env **env_list);
char	**env_to_array(t_env *env);
t_env	*array_to_env(char **env);
void	free_env_array(char **env);
void	add_env_var(t_env **env_list, char *key, char *value, bool exported);
int		env_var_cmp(t_env *a, t_env *b);
t_env	*new_env_var(char *key, char *value, bool exported);
void	free_env_list(t_env *env_list);
void	print_sorted_env(t_env *env_list);

#endif
