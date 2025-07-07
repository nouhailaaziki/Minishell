/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:27:23 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/06 21:36:23 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit"));
}

int	run_builtins(char **cmd, t_env **env_list, int status, t_stash *stash)
{
	status = 0;
	stash->return_status = 0;
	if (cmd && cmd[0])
	{
		if (!ft_strcmp("exit", cmd[0]))
		{
			run_exit(cmd, stash);
			status = stash->status;
		}
		else if (!ft_strcmp("env", cmd[0]))
			status = env(*env_list, stash, cmd);
		else if (!ft_strcmp("pwd", cmd[0]))
			status = pwd(stash);
		else if (!ft_strcmp("echo", cmd[0]))
			status = echo(cmd);
		else if (!ft_strcmp("cd", cmd[0]))
			status = cd(cmd, env_list, stash);
		else if (!ft_strcmp("unset", cmd[0]))
			status = unset(env_list, cmd, stash);
		else if (!ft_strcmp("export", cmd[0]))
			status = export(cmd, env_list, stash);
		else
			status = -1;
	}
	return (status);
}
