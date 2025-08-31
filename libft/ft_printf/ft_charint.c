/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:51:17 by gjacome-          #+#    #+#             */
/*   Updated: 2025/08/31 16:08:58 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printchar(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_printstring(int fd, char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (*str)
	{
		write(fd, str, 1);
		str++;
		count++;
	}
	return (count);
}

int	ft_printint(int fd, int n)
{
	int		count;
	char	*number;

	number = ft_itoa(n);
	count = write(fd, number, ft_strlen(number));
	free(number);
	return (count);
}

int	ft_printuint(int fd, unsigned int n)
{
	return (ft_putnbr_base(fd, n, BASE_10, 0));
}
