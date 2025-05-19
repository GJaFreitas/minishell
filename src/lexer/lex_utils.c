#include "lexer.h"
#include "minishell.h"

inline int	special_char(char c)
{
	return (ft_strchr(META_CHAR, c) != NULL);
}
