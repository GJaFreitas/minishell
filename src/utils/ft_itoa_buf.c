/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_buf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bag <gjacome-@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:47:23 by bag               #+#    #+#             */
/*   Updated: 2025/09/05 16:34:19 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_writenum(int c, char *s)
{
	while (*s)
		s++;
	*s = c;
}

static void	ft_putnbr(int nb, char *s)
{
	char	num;

	if (nb > 9)
	{
		ft_putnbr(nb / 10, s);
		ft_putnbr(nb % 10, s);
	}
	else
	{
		num = nb + '0';
		ft_writenum(num, s);
	}
}

static void	ft_putminus(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	s[i] = '-';
}

static void	init(char *temp)
{
	int	i;

	i = 0;
	while (i < 12)
	{
		temp[i] = 0;
		i++;
	}
}

void	ft_itoa_buf(long int n, char *buf, int size)
{
	char	temp[12];

	init(temp);
	if (n == -2147483648)
		ft_strlcpy(temp, "-2147483648", 12);
	else if (n < 0)
	{
		ft_putminus(temp);
		ft_putnbr(-n, temp);
	}
	else
		ft_putnbr(n, temp);
	ft_strlcpy(buf, temp, size);
}
