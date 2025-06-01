#include "libft.h"
#include "minishell.h"
#include "parser.h"

static char	*__append_until_quote(char **tokens, int *i);
char	*__append_token(char *t1, const char *t2);
int	__token_contains_quote(char *token);

/**********

new - ptr to a token

this is so that i can change it

***********/
int	__quote_handler(char **new, char **tokens)
{
	char	*final;
	int	i;

	i = 0;
	final = __append_until_quote(tokens, &i);
	*new = final;
	return (i);
}

/**********

This function calculates the size needed for the
final form of the token eg:

[ this"is"one"token" ] -> strlen(token)
[ this"is" two"tokens" ] -> strlen(token) + strlen(token+1)

***********/

static char	*__append_until_quote(char **tokens, int *i)
{
	char	*final;

	final = ft_strdup(tokens[*i]);
	*i += 1;
	while (tokens[*i])
	{
		final = __append_token(final, tokens[*i]);
		*i += 1;
		if (__token_contains_quote(tokens[*i]))
			break ;
	}
	return (final);
}
