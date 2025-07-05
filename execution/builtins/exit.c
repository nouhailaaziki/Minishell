/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:54:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/05 13:19:33 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	is_numeric(const char *str)
{
	if (!str || !*str)
		return (0);
	na_atoi(str);
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

void	run_exit(char **cmd, t_stash *stash)
{
	int	len;

	len = na_arrlen(cmd);
	if (!stash->exit_flag)
		ft_putendl_fd("exit", 2);
	if (len == 1)
	{
		free_all_tracked();
		exit((unsigned char)stash->status);
	}
	if (len > 2 && is_numeric(cmd[1]))
	{
		ft_putendl_fd("L33tShell: exit: too many arguments", 2);
		stash->status = 1;
		return ;
	}
	if (!is_numeric(cmd[1]))
	{
		free_all_tracked();
		(ft_putstr_fd("L33tShell: exit: ", 2), ft_putstr_fd(cmd[1], 2));
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	free_all_tracked();
	exit((unsigned char)na_atoi(cmd[1]));
}
