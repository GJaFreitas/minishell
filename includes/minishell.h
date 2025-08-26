#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "colors.h"
# include "memory.h"
# include <stdio.h>
# include <stdint.h>
# include <stdarg.h>
# include <stddef.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

# define CWD_BUFFER	1024


typedef struct s_redirect
{
	char				*args[2];
	struct s_redirect	*next;
}	t_redirect;

enum e_builtin
{
	UNKNOWN_COMMAND = -1,
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

/***************************
ENV ---------
****************************/

# define ENV_INIT_SIZE	128
typedef struct s_env
{
	char		**keys;
	char		**values;
	uint32_t	size;
	uint32_t	used;
	int		*sorted;
	char		**array;
	bool		dirty;
}	t_env;

t_env	*init_env(char **old);
void	env_free(t_env *env);
void	env_add(t_env *env, char *args);
void	env_remove(t_env *env, char *key);
void	env_print_sorted(t_env *env);
char	*env_get_value(t_env *env, char *key);
void	env_print(t_env *env);
char	**env_to_array(t_env *env);
void	free_env_array(char **arr);
int	env_var_exists(t_env *env, char *key);
char	*env_get_value_index(t_env *env, int index);
void	env_add_key_value_pair(t_env *env, char *key, char *value);

/* UTILITIES FOR ENV */
void	env_grow(t_env *env);
void	env_change_val(t_env *env, int index, char *val);
void	free_env(t_env *env);

/***************************
FUNCTIONS ---------
****************************/

int	ft_echo(char *const argv[], t_env *env);

int	ft_export(char *const argv[], t_env *env);

int	ft_pwd(char *const argv[], t_env *env);

int	ft_cd(char *const argv[], t_env *env);
int	get_full_dir_path(char *input, t_env *env, char full_path[][CWD_BUFFER]);
int	path_exists(char *path);

int	ft_unset(char *const argv[], t_env *env);

int	ft_env(char *const argv[], t_env *env);

int	ft_exit(char *const argv[], t_env *env);


/***************************
GENERAL MINISH ---------
****************************/

int	free_minishell(t_env *env, int exitcode);

/***************************
SIGNALS ---------
****************************/

void	signals(void);

/***************************
DEBUG ---------
****************************/

void	print_tokens(char *const *tokens);
void	print_cmd(t_cmd *cmd);
void	print_one_cmd(t_cmd *cmd);

/***************************
TEST ====================== */

// Add these function prototypes

void	ft_exec_all(t_cmd *cmd, t_env *env);
int		ft_strcmp(char *s1, char *s2);
char	*ft_itoa_buf(long int n, char *buf, int size);

#endif
