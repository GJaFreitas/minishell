#include "libft.h"
#include "minishell.h"

/*
* input -> "~/Documents/..."
* transformed into -> "$HOME/Documents/..."
* buf2 + 2 refers to everything after "~/"
* if a wrong path is given like "~Documents"
* the expansion will be "/home/userDocuments"
* making it wrong anyway and an error can be thrown after
*
* If the absolute path given starts with "/" then theres nothing
* that needs to be done and we can skip straight to the check if
* said path exists
*
* if a relative path is given the same logic that was applied to
* the expansion will be used, "." -> $CWD, "-" -> $OLD_PWD
*/

// buf2 starts at '~' or '.' meaning we want to skip that first char
static void	__assemble_path(char full_path[][CWD_BUFFER], char *buf1, char *buf2)
{
	int	i;

	i = 0;
	while (*buf1)
		(*full_path)[i++] = *buf1++;
	buf2++;
	while (*buf2)
		(*full_path)[i++] = *buf2++;
}

static int	__norm_helper(char full_path[][CWD_BUFFER], char *error)
{
	__assemble_path(full_path, "", "");
	printf("%s", error);
	return (1);
}

static int	__absolute_handler(char full_path[][CWD_BUFFER], char *input, t_env *env)
{
	char	*temp;

	if (input[0] == '~')
	{
		temp = env_get_value(env, "HOME");
		if (!temp)
			return (__norm_helper(full_path, "minishell: cd: HOME not set\n"));
		__assemble_path(full_path, temp, input);
	}
	else if (input[0] == '-')
	{
		temp = env_get_value(env, "OLD_PWD");
		if (!temp)
			return (__norm_helper(full_path, "minishell: cd: OLD_PWD not set\n"));
		ft_memcpy(*full_path, temp, ft_strlen(temp));
	}
	else
		ft_memcpy(*full_path, input, ft_strlen(input));
	return (0);
}

static void	__relative_handler(char full_path[][CWD_BUFFER], char *input, t_env *env)
{
	char	*temp;

	temp = env_get_value(env, "PWD");
	if (input[0] == '.')
	{
		__assemble_path(full_path, temp, input);
		if (input[1] == '.')
			*ft_strrchr(*full_path, '/') = 0;
	}
	else
	{
		ft_memcpy(*full_path, temp, ft_strlen(temp));
		(*full_path)[ft_strlen(temp)] = '/';
		ft_memcpy(*full_path + ft_strlen(temp) + 1, input, ft_strlen(input));
	}
}

// Assume input is valid and not NULL
int	get_full_dir_path(char *input, t_env *env, char full_path[][CWD_BUFFER])
{
	if (ft_strchr("/~-", input[0]))
		return (__absolute_handler(full_path, input, env));
	else
		__relative_handler(full_path, input, env);
	return (0);
}
