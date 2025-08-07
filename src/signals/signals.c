/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:01:30 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/08/07 18:01:31 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

extern int	g_sig;

void	__sigint_h(int code)
{
	(void)code;
}

void	signals(void)
{
	signal(SIGINT, __sigint_h);
}
