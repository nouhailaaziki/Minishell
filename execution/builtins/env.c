/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:25:04 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/21 13:52:07 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	env(t_env *env_list, t_stash *stash, char **cmd)
{
	int	len;
	int	i;

	i = 0;
	len = na_arrlen(cmd);
	while (!ft_strcmp(cmd[i], "env") && i < len)
		i++;
	if (ft_strcmp(cmd[i], "env") && i != len)
		return (execute_command(&cmd[i], NULL, &env_list, stash));
	else
	{
		if (!env_list)
			ft_putendl_fd("L33tShell: env: No such file or directory", 2);
		while (env_list)
		{
			if (stash->path_flag == 1 && !ft_strcmp(env_list->key, "PATH"))
				env_list = env_list->next;
			if (env_list)
				if (env_list->value || !ft_strcmp(env_list->value, ""))
					printf("%s=%s\n", env_list->key, env_list->value);
			if (env_list)
				env_list = env_list->next;
		}
	}
	return (0);
}
