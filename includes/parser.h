/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:50:50 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/09/06 17:12:23 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "stdbool.h"
# include <sys/types.h>

# define REDIRECT	"<>"	

# define NO_PATH_VAR	-1
# define UNKNOW_CMD		-2

# include "minishell.h"

typedef struct s_hdoc
{
	t_env	*env;
	char	**delimiter;
	int		fd;
}	t_hdoc;

typedef struct s_expansion_list
{
	char					*expansion;
	bool					allocd;
	struct s_expansion_list	*next;
}	t_string_list;

t_cmd			*parser(char **tokens, t_env *env, char **env_array);
t_cmd			*assign_cmds(char **tokens, char **env);
t_cmd			*__init_cmd(void);
char			*path_search(char *token, char **env, enum e_builtin *cmd);
int				is_pipe(char *token);
void			expansions(char **tokens, char **env, int exit);
void			heredocs(char **tokens, t_env *env);

// Utils ------------------
void			free_tokens(char **tokens);
char			*ft_strndup(const char *s, int n);
char			*__rel_path_srch(char *token, int *flag);
char			*__path_extract(char **env);
char			*__env_path_srch(char *token, char **env, int *flag);
t_string_list	*next_expansion(t_string_list *list);
char			*__get_expansion(char *tok, char **env);
int				get_expansion_size(char *tok);
char			*__assemble(t_string_list *list, int size);
int				expansion_list_size(t_string_list *expansions);
char			*__search_folders(char **folders, char *token);
int				assign_command(t_cmd *cmd, char **tokens, char **env);
char			*__get_expansion(char *tok, char **env);
int				get_expansion_size(char *tok);
char			*__assemble(t_string_list *list, int size);
int				expansion_list_size(t_string_list *expansions);
char			*__search_folders(char **folders, char *token);
t_hdoc			*hdoc_norm(t_hdoc *ptr);

// Para chamar no exec ou na main depois
void			free_cmds(t_cmd *cmds);
// ------------------

/*********************
Parser debugging
*********************/
void			parser_debug(char **tokens);

#endif
