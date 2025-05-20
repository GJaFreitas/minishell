#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>

/*******************************

ls -la a* |grep me > outfile

cat -e <infile | grep a

ls dir|grep a

********************************/

int	meta_char_handler(char *s, int i, char *str)
{
	int	count;

	count = 0;
	if (i-1 >= 0 && s[i-1] != ' ' && !special_char(s[i-1]))
		str[count++] = ' ';
	str[count++] = s[i];
	if (s[i+1] != ' ' && !special_char(s[i+1]))
		str[count++] = ' ';
	return (count);
}

// Inserts spaces where necessary so that split()
// can tokenize the string;
// Precondition: s != NULL;
static char	*prepare_tokenize(char *s)
{
	unsigned int	i;
	unsigned int	j;
	char		*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(s) * 2);
	while (s[i] && s[i + 1])
	{
		if (special_char(s[i]))
			j += meta_char_handler(s, i, str + j);
		else
			str[j++] = s[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

void	remove_newline(char *line)
{
	while (line && *line)
	{
		if (*line == '\n')
			*line = 0;
		line++;
	}
}

char	**lexer(char *line)
{
	char	**toks;
	char	*tokenizable;

	remove_newline(line);
	if (!*line)
		return (free(line), NULL);
	tokenizable = prepare_tokenize(line);
	toks = ft_split(tokenizable);
	free(line);
	free(tokenizable);
	return (toks);
}
