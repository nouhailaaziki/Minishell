/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:54:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/09 15:04:16 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	is_numeric(const char *str)
{
	long long	i;

	if (!str || !*str)
		return (0);
	i = ft_atoi(str);
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

void	run_exit(char **argv, int argc, int last_status)
{
	write(1, "exit\n", 5);
	if (argc == 2)
		exit((unsigned char)last_status);
	if (argc > 3)
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	if (!is_numeric(argv[2]))
	{
		printf("minishell: exit: %s: numeric argument required\n", argv[2]);
		exit(2);
	}
	exit((unsigned char)ft_atoi(argv[2]));
}
