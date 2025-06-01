#include "libft.h"
#include "parser.h"
#include "minishell.h"
#include "structs.h"

// Frees t1
char	*__append_token(char *t1, char *t2);
int	__token_contains_quote(char *token);
int	__quote_handler(char **new, char **tokens);

static int	__get_token_count(char **tokens);
static void	__cpy_tokens(char **new, char **tokens);

void	token_merge(char ***tokens)
{
	char	**new;

	new = malloc(sizeof(char *) * (__get_token_count(*tokens) + 1));
	__cpy_tokens(new, *tokens);
	free_tokens(*tokens);
	free(*tokens);
	*tokens = new;
}

static int	__get_token_count(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (ft_strchr(QUOTES, tokens[i++][0]))
		{
			while (tokens[i] && !ft_strchr(QUOTES, tokens[i][0]))
				i++;
		}
		count++;
	}
	return (count);
}

static void	__cpy_tokens(char **new, char **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (__token_contains_quote(tokens[i]))
			i += __quote_handler(&new[j], &tokens[i]);
		else
			new[j] = ft_strdup(tokens[i]);
		i++;
		j++;
	}
}
