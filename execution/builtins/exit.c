/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:54:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/23 09:39:25 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	is_numeric(const char *str)
{
	if (!str || !*str)
		return (0);
	strict_atoi(str);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	run_exit(char **cmd, int exit_status)
{
	int	len;

	len = ft_arrlen(cmd);
	printf("exit\n");
	if (len == 1)
	{
		free_all_tracked();
		exit((unsigned char)exit_status);
	}
	if (len > 2)
	{
		free_all_tracked();
		printf("L33tShell: exit: too many arguments\n");
		return ;
	}
	if (!is_numeric(cmd[1]))
	{
		free_all_tracked();
		printf("L33tShell: exit: %s: numeric argument required\n", cmd[1]);
		exit(255);
	}
	free_all_tracked();
	exit((unsigned char)strict_atoi(cmd[1]));
}
