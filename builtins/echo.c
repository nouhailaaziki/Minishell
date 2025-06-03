/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:15:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/03 19:16:48 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	echo(char **cmd)
{
	int	i;
	int	n;

	i = 1;
	if (!cmd[1])
		return (printf("\n"), 0);
	while (cmd[i] && cmd[i][0] == '-' && ft_isallchar(&cmd[i][1], 'n'))
		i++;
	n = i;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i])
			printf(" ");
		i++;
	}
	if (n == 1)
		printf("\n");
	return (0);
}
