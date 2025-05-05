/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/05 17:51:03 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

void	executor(char **argv, int argc, t_env **env_list)
{
	int	last_status;

	last_status = 0;
	if (argv[1])
	{
		if (ft_strcmp("env", argv[1]) == 0
			|| ft_strcmp("ENV", argv[1]) == 0)
			run_env(env_list);
		if (ft_strcmp("echo", argv[1]) == 0
			|| ft_strcmp("ECHO", argv[1]) == 0)
			run_echo(argv);
		if (ft_strcmp("exit", argv[1]) == 0)
			run_exit(argv, argc, last_status);
		if (ft_strcmp("cd", argv[1]) == 0
			|| ft_strcmp("CD", argv[1]) == 0)
			run_cd(argv, env_list);
		if (ft_strcmp("pwd", argv[1]) == 0
			|| ft_strcmp("PWD", argv[1]) == 0)
			run_pwd(env_list);
	}
}
