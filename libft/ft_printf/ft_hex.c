/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:52:23 by gjacome-          #+#    #+#             */
/*   Updated: 2025/08/31 16:11:11 by bag              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printptr(int fd, void *v)
{
	unsigned long int	ptr;
	int					count;

	ptr = (unsigned long int) v;
	if (ptr == 0)
		return (write(fd, "(nil)", 5));
	count = write(fd, "0x", 2);
	count += ft_putnbr_base(fd, ptr, HEX_LOW, 0);
	return (count);
}

int	ft_printhexsmall(int fd, unsigned int n)
{
	return (ft_putnbr_base(fd, n, HEX_LOW, 0));
}

int	ft_printhexbig(int fd, unsigned int n)
{
	return (ft_putnbr_base(fd, n, HEX_UP, 0));
}
