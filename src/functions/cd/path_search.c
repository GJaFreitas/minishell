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

static void	__assemble_path(char full_path[][CWD_BUFFER], char *buf1, char *buf2)
{
	ft_memcpy(*full_path, buf1, ft_strlen(buf2));
	ft_memcpy(*full_path + ft_strlen(buf1), buf2 + 2, ft_strlen(buf2));
}

static void	__absolute_handler(char full_path[][CWD_BUFFER], char *input, t_env *env)
{
	char	*temp;

	if (input[0] == '~')
	{
		temp = env_get_value(env, "HOME");
		if (!temp) return ;
		// HOME NOT SET ERROR
		__assemble_path(full_path, temp, input);
	}
	else if (input[0] == '-')
	{
		temp = env_get_value(env, "OLD_PWD");
		ft_memcpy(*full_path, temp, ft_strlen(temp));
	}
}

static void	__relative_handler(char full_path[][CWD_BUFFER], char *input, t_env *env)
{
	char	*temp;

	temp = env_get_value(env, "PWD");
	if (input[0] == '.')
	{
		input[0] = '/';
		__assemble_path(full_path, temp, input);
	}
	else
	{
		ft_memcpy(*full_path, temp, ft_strlen(temp));
		*full_path[ft_strlen(temp)] = '/';
		ft_memcpy(*full_path + ft_strlen(temp) + 1, input, ft_strlen(input));
	}
}

void	get_full_dir_path(char *input, t_env *env, char full_path[][CWD_BUFFER])
{
	if (ft_strchr("/~-", input[0]))
		__absolute_handler(full_path, input, env);
	else
		__relative_handler(full_path, input, env);
}
