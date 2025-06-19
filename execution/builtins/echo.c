/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:15:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/17 09:54:28 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	echo(char **cmd)
{
	int	i;
	int	n;

	i = 1;
	if (!cmd[1])
		return (write(1, "\n", 1), 0);
	while (cmd[i] && cmd[i][0] == '-' && ft_isallchar(&cmd[i][1], 'n'))
		i++;
	n = i;
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n == 1)
		write(1, "\n", 1);
	return (0);
}
