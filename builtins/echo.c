/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:15:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/04 11:50:28 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	run_echo(char **argv)
{
	int	i;

	if ((ft_strcmp("-n", argv[2])) == 0)
		i = 3;
	else
		i = 2;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i])
			ft_putchar_fd(32, 1);
	}
	if ((ft_strcmp("-n", argv[2])) != 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
