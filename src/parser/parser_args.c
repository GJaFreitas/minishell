#include "libft.h"
#include "parser.h"
#include "structs.h"

char	*__append_token(char *t1, const char *t2)
{
	char	*token;
	t_uint	sizet1;
	t_uint	sizet2;

	sizet1 = ft_strlen(t1);
	sizet2 = ft_strlen(t2);
	token = malloc(sizet1 + sizet2 + 2);
	ft_memcpy(token, t1, sizet1);
	token[sizet1++] = ' ';
	ft_memcpy(token + sizet1, t2, sizet2);
	token[sizet1 + sizet2] = 0;
	free(t1);
	return (token);
}

static char	*__args_create(char *token)
{
	char	*args;
	t_uint	size;

	size = ft_strlen(token);
	args = malloc(size + 1);
	ft_memcpy(args, token, size);
	args[size] = 0;
	return (args);
}

int	__args(t_simplecmd *cmd, char *token)
{
	if (!cmd->args)
		cmd->args = __args_create(token);
	else
		cmd->args = __append_token(cmd->args, token);
	return (0);
}
