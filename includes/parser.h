#ifndef PARSER_H
# define PARSER_H

#include "stdbool.h"
#include <sys/types.h>

# define REDIRECT	"<>"

# define HDOC_EOF	(1 << 31)

# define NO_PATH_VAR	-1
# define UNKNOW_CMD	-2

# include "minishell.h"

typedef struct s_expansion_list
{
	char	*expansion;
	bool	allocd;
	struct s_expansion_list	*next;
}	t_string_list;

t_cmd	*parser(char **tokens, t_env *env, char **env_array);
t_cmd	*assign_cmds(char **tokens, char **env);
t_cmd	*__init_cmd(void);
char	*path_search(char *token, char **env, enum e_builtin *cmd);
int		is_pipe(char *token);
void	expansions(char **tokens, char **env, int exit);
void	heredocs(char **tokens, char **env);


// Utils ------------------
void	free_tokens(char **tokens);
char	*ft_strndup(const char *s, int n);

// Para chamar no exec ou na main depois
void	free_cmds(t_cmd *cmds);
// ------------------

/*********************
Parser debugging
*********************/
void	parser_debug(char **tokens);

#endif
