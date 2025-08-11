#include "minishell.h"

char	*ft_strndup(const char *s, int n)
{
	char	*new_str;
	int		strlen;

	if (ft_strlen(s) < n)
		return (NULL);
	new_str = malloc(n + 1);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s, n + 1);
	return (new_str);
}
