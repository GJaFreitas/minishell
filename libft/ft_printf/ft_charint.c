/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:51:17 by gjacome-          #+#    #+#             */
/*   Updated: 2025/04/30 00:51:18 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printstring(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (*str)
	{
		write(1, str, 1);
		str++;
		count++;
	}
	return (count);
}

int	ft_printint(int n)
{
	int		count;
	char	*number;

	number = ft_itoa(n);
	count = write(1, number, ft_strlen(number));
	free(number);
	return (count);
}

int	ft_printuint(unsigned int n)
{
	return (ft_putnbr_base(n, BASE_10, 0));
}
