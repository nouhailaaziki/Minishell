/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:15:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/13 11:15:20 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/launchpad.h"

int	run_echo(char **argv)
{
	int	i;
	int	n;

	if (!argv[2])
		return (printf("\n"), 0);
	if (argv[2][0] == '-' && is_all_char(&argv[2][1], 'n'))
		n = 3;
	else
		n = 2;
	i = n;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i])
			ft_putchar_fd(32, 1);
	}
	if (n != 3)
		ft_putchar_fd('\n', 1);
	return (0);
}
