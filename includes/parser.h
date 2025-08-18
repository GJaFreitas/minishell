#ifndef PARSER_H
# define PARSER_H

# define REDIRECT	"<>"

# include "minishell.h"

typedef struct s_expansion_list
{
	char	*expansion;
	struct s_expansion_list	*next;
}	t_expansion_list;

t_cmd	*parser(char **tokens, t_env *env, char **env_array);
t_cmd	*assign_cmds(char **tokens, char **env);
t_cmd	*__init_cmd(void);
char	*path_search(char *token, char **env);
int		is_pipe(char *token);
void	expansions(char **tokens, char **env);


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
