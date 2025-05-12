/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/12 12:27:36 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/launchpad.h"

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
			run_exit(argv, argc, last_status, env_list);
		if (ft_strcmp("cd", argv[1]) == 0
			|| ft_strcmp("CD", argv[1]) == 0)
			run_cd(argv, env_list);
		if (ft_strcmp("pwd", argv[1]) == 0
			|| ft_strcmp("PWD", argv[1]) == 0)
			run_pwd(env_list);
		if (ft_strcmp("unset", argv[1]) == 0)
			run_unset(env_list, argv);
		if (ft_strcmp("export", argv[1]) == 0)
			run_export(argc, argv, env_list);
	}
}
