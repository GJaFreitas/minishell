/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:52:23 by gjacome-          #+#    #+#             */
/*   Updated: 2025/04/30 00:52:24 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printptr(void *v)
{
	unsigned long int	ptr;
	int					count;

	ptr = (unsigned long int) v;
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	count += ft_putnbr_base(ptr, HEX_LOW, 0);
	return (count);
}

int	ft_printhexsmall(unsigned int n)
{
	return (ft_putnbr_base(n, HEX_LOW, 0));
}

int	ft_printhexbig(unsigned int n)
{
	return (ft_putnbr_base(n, HEX_UP, 0));
}
