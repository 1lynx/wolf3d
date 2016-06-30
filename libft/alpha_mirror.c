/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_mirror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrandria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 15:52:21 by nrandria          #+#    #+#             */
/*   Updated: 2015/09/24 16:25:59 by nrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		alpha_mirror(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc == 2)
	{
		while (argv[1][i] != '\0')
		{
			if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
			{
				argv[1][i] = 219 - argv[1][i];
				ft_putchar(argv[1][i]);
			}
			else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
			{
				argv[1][i] = 155 - argv[1][i];
				ft_putchar(argv[1][i]);
			}
			else
				ft_putchar(argv[1][i]);
			i++;
		}
		ft_putchar('\n');
	}
	else
		ft_putchar('\n');
}
