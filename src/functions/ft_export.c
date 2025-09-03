/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:53:48 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/09/03 18:38:47 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
void	__rm_quote_arg(char *arg);

inline static int	__error_msg(char *const args)
{
	ft_fprintf(2, "minishell: export: %s: not a valid identifier\n", args);
	return (0);
}

// 0 not valid
static int	__check_valid_env(char *const args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '=')
			break ;
		if (!is_env_char(args[i]))
			return (__error_msg(args));
		i++;
	}
	return (1);
}

static void	__remove_quotes(char *arg)
{
	while (*arg)
	{
		if (ft_strchr(QUOTES, *arg))
			ft_memcpy(arg, arg + 1, ft_strlen(arg + 1) + 1);
		arg++;
	}
}

static char	**__check_args(int argc, char *const args[])
{
	char	**tokens;
	int	i;

	i = 0;
	tokens = ft_calloc((argc + 1), sizeof(char *));
	while (*args)
	{
		if (__check_valid_env(*args))
			tokens[i++] = ft_strdup(*args);
		args++;
	}
	i = 0;
	while (tokens[i])
	{
	       __remove_quotes(tokens[i]);
		i++;
	}
	return (tokens);
}

int	ft_export(char *const argv[], t_env *env)
{
	char	**tokens;
	int	i;
	int	retval;
	int	arg_count;

	i = 0;
	retval = 0;
	arg_count = count_args(argv);
	if (arg_count > 1)
	{
		tokens = __check_args(arg_count, argv + 1);
		while (tokens[i])
		{
			if (tokens[i][0])
				retval = env_add(env, tokens[i]);
			i++;
		}
		free_tokens(tokens);
		free(tokens);
	}
	else
		env_print_sorted(env);
	return (retval);
}
