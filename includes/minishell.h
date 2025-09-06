/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:50:46 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/09/06 17:10:02 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "memory.h"
# include "signals.h"
# include <dirent.h>
# include <stdio.h>
# include <stdint.h>
# include <stdarg.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

# define HDOC_ERROR1 "minishell: warning: here-document at "
# define HDOC_ERROR2 "line %d delimited by end-of-file (wanted %s)\n"

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
	int				status;
	char			**args;
	enum e_builtin	builtin;
	int				redirect_in;
	int				redirect_out;
	t_redirect		*redirect;
	struct s_cmd	*next;
}	t_cmd;

/***************************
ENV ---------
****************************/

# define ENV_INIT_SIZE	128
# define ENV_SORTING	1
# define ENV_ARRAYING	2

enum e_env_dirt
{
	ENV_DIRTY = 0,
	ENV_A,
	ENV_S,
	ENV_CLEAN
};

typedef struct s_env
{
	char			**keys;
	char			**values;
	int				*sorted;
	char			**array;
	uint32_t		size;
	uint32_t		used;
	int				exit;
	enum e_env_dirt	dirty;
}	t_env;

int				is_env_clean(t_env *env, int flag);
t_env			*init_env(char **old);
void			env_free(t_env *env);
int				env_add(t_env *env, char *args);
void			env_remove(t_env *env, char *key);
void			env_print_sorted(t_env *env);
char			*env_get_value(t_env *env, char *key);
void			env_print(t_env *env);
char			**env_to_array(t_env *env);
void			free_env_array(char **arr);
int				env_var_exists(t_env *env, char *key);
char			*env_get_value_index(t_env *env, int index);
void			env_add_key_value_pair(t_env *env, char *key, char *value);

/* UTILITIES FOR ENV */
void			env_grow(t_env *env);
void			env_change_val(t_env *env, int index, char *val);
void			free_env(t_env *env);
int				is_env_char(int c);
t_cmd			*norm(t_cmd *cmd);
enum e_env_dirt	clean_env(t_env *env, int flag);

/***************************
FUNCTIONS ---------
****************************/

int				ft_echo(char *const argv[], t_env *env);
int				ft_export(char *const argv[], t_env *env);
int				ft_pwd(char *const argv[], t_env *env);
// CD
int				ft_cd(char *const argv[], t_env *env);
int				get_full_dir_path(char *input, t_env *env,
					char full_path[][CWD_BUFFER]);
int				path_exists(char *path);
// ---
int				ft_unset(char *const argv[], t_env *env);
int				ft_env(char *const argv[], t_env *env);
int				ft_exit(char *const argv[], t_env *env);

int				count_args(char *const argv[]);
/***************************
GENERAL MINISH ---------
****************************/

int				free_minishell(t_env *env, int exitcode);

/***************************
SIGNALS ---------
****************************/

void			signals(void);
int				sig_response(int sig, int status);
/***************************
DEBUG ---------
****************************/

void			print_tokens(char *const *tokens);
void			print_cmd(t_cmd *cmd);
void			print_one_cmd(t_cmd *cmd);

/***************************
EXEC ----------------
****************************/

int				ft_exec_all(t_cmd *cmd, t_env *env);
void			exec_builtin(t_cmd *cmd, t_env *env, int in, int out);
int				setup_redirections(t_cmd *cmd);
void			setup_pipes(t_cmd *cur, int *in, int *out, int pipefd[2]);
void			ft_exec(t_cmd *cmd, t_env *env, int in, int out);
int				wait_pids(t_cmd *cmds, t_env *env);
void			dups(int *stdin_fd, int *stdout_fd, int in, int out);
void			unknow_cmd(t_cmd *cmd, t_env *env);

/***************************
UTILS ----------------
****************************/
int				ft_strcmp(const char *s1, const char *s2);
void			ft_itoa_buf(long int n, char *buf, int size);

#endif
