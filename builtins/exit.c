/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:54:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/12 16:15:03 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/launchpad.h"

int	is_numeric(const char *str, t_env **env_list)
{
	long	i;

	if (!str || !*str)
		return (0);
	i = parse_number_or_exit(str, env_list);
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

void	run_exit(char **argv, int argc, int last_status, t_env **env_list)
{
	write(1, "exit\n", 5);
	if (argc == 2)
	{
		free_env_list(env_list);
		exit((unsigned char)last_status);
	}
	if (argc > 3)
	{
		free_env_list(env_list);
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	if (!is_numeric(argv[2], env_list))
	{
		free_env_list(env_list);
		printf("minishell: exit: %s: numeric argument required\n", argv[2]);
		exit(2);
	}
	free_env_list(env_list);
	exit((unsigned char)parse_number_or_exit(argv[2], env_list));
}
