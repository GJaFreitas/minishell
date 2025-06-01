#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>

static int	__dollah_sign(char *s);
static int	__substitute_var(char *s, char *env_var);

void	__expansions(char **line, size_t mem)
{
	char	*s;
	char	*env_var;
	int	i;

	s = *line;
	i = 0;
	printf("%s\n", *line);
	while (s[i])
	{
		i += __dollah_sign(&s[i]);
		if (!s[i])
			break ;
		env_var = getenv(&s[i]);
		if (mem < (ft_strlen(*line) + ft_strlen(env_var)))
		{
			*line = ft_realloc(*line, mem, (mem + ft_strlen(env_var)) * 2);
			s = *line;
		}
		i += __substitute_var(&s[i], env_var);
	}
	printf("%s\n", *line);
}

static int	__substitute_var(char *s, char *env_var)
{
	char	*rest;
	int	i;

	i = 0;
	while (s[i] && !ft_strchr(QUOTES, s[i]) \
	&& !ft_strchr(META_CHAR, s[i]) && !ft_isspace(s[i]))
		i++;
	rest = ft_strdup(s + i + 1);
	i = ft_strlen(env_var);
	ft_memcpy(s, env_var, i);
	ft_memcpy(s + i, rest, ft_strlen(rest) + 1);
	return (i);
}

static int	__dollah_sign(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			while (s[i] && s[++i] != '\'')
				;
		if (s[i] == '$')
			return (i);
		if (!s[i])
			break ;
		i++;
	}
	return (i);
}
