#include "parser.h"
#include "libft.h"

int	is_pipe(char *token)
{
	return (*token == '|');
}

int	__token_contains_quote(char *token)
{
	if (!token)
		return (0);
	while (*token)
	{
		if (ft_strchr(QUOTES, *token))
			return (1);
		else
			token++;
	}
	return (0);
}
