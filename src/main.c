/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:07:36 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/22 12:05:55 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include <readline/readline.h>
#include <readline/history.h>

pid_t	g_sig;

int	free_minishell(t_env *env, int exitcode)
{
	free_env(env);
	printf("exit\n");
	return (exitcode);
}

t_cmd	*prompt(t_env *env)
{
	char		*line;
	static char	cwd[CWD_BUFFER];

	ft_bzero(cwd, CWD_BUFFER);
	if (!getcwd(cwd, CWD_BUFFER))
		perror("getcwd() error\n");
	ft_memcpy(cwd + ft_strlen(cwd), " »  ", 4);
	line = readline(cwd);
	if (!line)
		exit (free_minishell(env, 0));
	return (parser(lexer(line), env, env_to_array(env)));
}

static void	shell_loop(t_env *env)
{
	t_cmd	*cmd;
	while (1)
	{
		cmd = prompt(env);
		ft_exec_all(cmd, env);
	}
	
}

int	main(int argc, char **argv, char **env)
{
	t_env *env_t;

	(void)argc;
	(void)argv;
	env_t = init_env(env);
	signals();
	shell_loop(env_t);
	return (0);
}
