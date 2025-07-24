#include "libft.h"
#include "minishell.h"

static int	_strncmp(const char *s1, const char *s2, size_t n)
{
	if (s2 == NULL)
		return (1);
	if (n == 0)
		return (0);
	while (*s1 && (*s1 == *s2) && --n > 0)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	ft_echo(char *const argv[], char *const env[])
{
	int	i;
	int	flag;

	(void)env;
	i = 0;
	flag = 1;
	if (!_strncmp("-n\0", argv[i], 3))
	{
		flag = 0;
		i++;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i++]);
		if (argv[i])
			write(1, " ", 1);
	}
	if (flag || !argv[0])
		write(1, "\n", 1);
	exit(0);
}
