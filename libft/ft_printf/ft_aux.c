/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacome- <gjacome-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:51:36 by gjacome-          #+#    #+#             */
/*   Updated: 2025/04/30 00:51:37 by gjacome-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_base(unsigned int nbr, char *base, int total)
{
	int		bl;
	char	c;

	bl = ft_strlen(base);
	if ((nbr / bl) > 0)
	{
		total = ft_putnbr_base(nbr / bl, base, total);
		total = ft_putnbr_base(nbr % bl, base, total);
	}
	else
	{
		c = base[nbr];
		total += write(1, &c, 1);
	}
	return (total);
}
