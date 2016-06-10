/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrandria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/25 15:13:55 by nrandria          #+#    #+#             */
/*   Updated: 2015/09/25 16:13:22 by nrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				print_bits(unsigned char octet)
{
	unsigned int	i;

	i = 128;
	while (i > 0)
	{
		if (i & octet)
			ft_putchar('1');
		else
			ft_putchar('0');
		i = i / 2;
	}
}
