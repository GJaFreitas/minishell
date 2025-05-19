#include "minishell.h"

// Account for how spaces and tabs were removed
char	*ft_reverse_split(char **tokens)
{
	size_t	len;
	size_t	i;
	char	*str;

	i = 0;
	len = 0;
	while (tokens[i] && tokens[i][0] != '|')
	{
		len += ft_strlen(tokens[i]);
		len++;
		i++;
	}
	str = ft_calloc(1, len + 1);
	i = 0;
	while (tokens && *tokens)
	{
		len = ft_strlen(*tokens);
		ft_memcpy(&str[i], *tokens, len);
		i += len;
		str[i++] = ' ';
		tokens++;
	}
	str[i] = '\n';
	return (str);
}

void	ft_echo(char **tokens)
{
	char	*result;

	result = NULL;
	if (*tokens && ft_strncmp(*tokens, "-n", 2))
		result = ft_reverse_split(tokens);
	ft_printf("%s", result);
}
