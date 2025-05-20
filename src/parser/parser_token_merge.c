#include "libft.h"
#include "parser.h"
#include "structs.h"

// Frees t1
char	*__append_token(char *t1, char *t2);

// -1 is an unclosed quote
// eg: echo "no quote closing\n
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
			if (tokens[i] == NULL)
				return (-1);
		}
		count++;
	}
	return (count);
}

static int	__quote_append(char **new, char **tokens)
{
	char	*token;
	int	i;

	i = 1;
	token = ft_strdup(tokens[i]);
	while (tokens[i] && ft_strchr(QUOTES, tokens[i][0]))
	{
		token = __append_token(token, tokens[i]);
		i++;
	}
	token = __append_token(token, tokens[i]);
	*new = token;
	return (i);
}

static void	__cpy_tokens(char **new, char **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (ft_strchr(QUOTES, tokens[i][0]))
			i += __quote_append(&new[j], &tokens[i]);
		else
			new[j] = ft_strdup(tokens[i]);
		i++;
		j++;
	}
}

void	token_merge(char ***tokens)
{
	char	**new;
	int	token_final_count;

	token_final_count = __get_token_count(*tokens);
	if (token_final_count == -1)
		return ; // @TODO: Error here
	new = malloc(sizeof(char *) * (token_final_count + 1));
	__cpy_tokens(new, *tokens);
	free(*tokens);
	*tokens = new;
}
