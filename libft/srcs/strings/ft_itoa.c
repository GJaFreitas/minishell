/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:21:32 by gjacome-          #+#    #+#             */
/*   Updated: 2024/08/19 15:33:59 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

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

char	*ft_itoa(long int n)
{
	char	*str;
	char	temp[12];
	int		size;

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
	size = ft_strlen(temp);
	str = malloc(size + 1);
	ft_strlcpy(str, temp, size + 1);
	return (str);
}
