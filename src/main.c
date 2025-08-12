/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:07:36 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/12 17:58:48 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include <readline/readline.h>
#include <readline/history.h>

int	g_sig;

t_cmd	*prompt(t_env *env)
{
	char *line;
	static char cwd[CWD_BUFFER];

	if (!getcwd(cwd, CWD_BUFFER))
		perror("getcwd() error\n");
	ft_memcpy(cwd + ft_strlen(cwd) - 1, " » ", 4);
	line = readline(cwd);
	if (!line)
		exit(0);
	return (parser(lexer(line), env));
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
	shell_loop(env_t);
	return (0);
}
