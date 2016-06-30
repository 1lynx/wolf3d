/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrandria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 16:58:06 by nrandria          #+#    #+#             */
/*   Updated: 2016/02/20 20:29:40 by nrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	do_op(int ac, char **av)
{
	int	nb1;
	int	nb2;
	int	result;

	nb1 = ft_atoi(av[1]);
	nb2 = ft_atoi(av[3]);
	result = 0;
	if (ac == 4 && av[2][1] == '\0')
	{
		if (av[2][0] == '+')
			result = nb1 + nb2;
		else if (av[2][0] == '-')
			result = nb1 - nb2;
		else if (av[2][0] == '*')
			result = nb1 * nb2;
		else if (av[2][0] == '/')
			result = nb1 / nb2;
		ft_putnbr(result);
		ft_putchar('\n');
	}
	else
		ft_putchar('\n');
}
