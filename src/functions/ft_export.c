#include "libft.h"
#include "export.h"
#include "minishell.h"

/* ivar -> internal variable */
//
// static void	__print_env(char *const env[])
// {
// 	int	i;
//
// 	i = 0;
// 	if (!env)
// 		return ;
// 	while (env[i])
// 	{
// 		write(1, "declare -x ", 11);
// 		write(1, "\"", 1);
// 		ft_printf("%s", env[i++]);
// 		write(1, "\"", 1);
// 		write(1, "\n", 1);
// 	}
// }
//
// /*
//  * export <var>=<value>
//  * export <var>="<value>"
// */
//
// static char	*__create_string(char *const argv[])
// {
// 	char	*new_entry;
//
// 	return (new_entry);
// }
//
// static void	__env_set(char *const env[], char *new)
// {
// }
//
// /*
//  * <var>=<value>	- Create internal var, if var has been
//  * 			- set to export already then do so if not
//  * 			- simply keep as internal
//  *
//  * export <var>		- Set var to be exported, if var already
//  * 			- existed then export it with its value,
//  * 			- if not then keep as internal marked for export
// */
//
// static void	__internal_var(char *const env[], t_ivar *_ivars, char *new)
// {
// 	char	*sep;
//
// 	sep = ft_strchr(new, '=');
// 	if (sep)
// 	{
// 		while (_ivars && ft_strncmp(new, (_ivars++)->var, sep - new))
// 	}
// }
//
int	ft_export(char *const argv[], char *const env[])
{
	(void)argv;
	(void)env;
	printf("Implement export\n");
	exit(0);
	// static t_ivar	**_ivars;
	// char	*new_entry;
	//
	// if (!argv || !*argv)
	// 	return (__print_env(env), 0);
	// while (*argv)
	// {
	// 	new_entry = __create_string(argv);
	// 	if (new_entry == NULL)
	// 		continue ;
	// 	if (ft_strchr(new_entry, '='))
	// 		__env_set(env, new_entry);
	// 	else
	// 		__internal_var(env, _ivars, new_entry);
	// 	argv++;
	// }
	// return (0);
}
