#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "structs.h"

static int	__cur_size(char *opts)
{
	int	size;

	size = ft_strlen(opts);
	return (next_div_8(size));
}

// Because strlcat is so weird like idk what it does
static void	ft_strcat(char **dst, const char *src)
{
	char	*new;
	t_uint	srcsize;
	t_uint	cur_size;
	t_uint	dstsize;

	dstsize = ft_strlen(*dst);
	srcsize = ft_strlen(src);
	cur_size = __cur_size(*dst);
	if (srcsize + dstsize >= cur_size)
	{
		new = ft_realloc(*dst, cur_size, next_div_8(dstsize + srcsize));
		free(*dst);
	}
	ft_memcpy(new + dstsize, src, srcsize);
}

// Allocates memory for the opts in chunks of 8
static char	*__opts_create(t_uint count, char *token)
{
	char	*opts;

	count = next_div_8(count);
	opts = ft_calloc(count + 1, sizeof(char));
	ft_strlcpy(opts, token, count);
	return (opts);
}

int	__options(t_simplecmd *cmd, char *token)
{
	unsigned int	count;
	unsigned int	i;
	char		*opts;

	i = 0;
	if (token[i++] != '-')
		return (1);
	while (token[i])
	{
		count++;
		i++;
	}
	if (!count)
		return (2);
	opts = cmd->opts;
	if (!opts)
		cmd->opts = __opts_create(count, token + 1);
	else
		ft_strcat(&cmd->opts, token + 1);
	return (0);
}
