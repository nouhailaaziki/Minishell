/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:58:23 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/27 11:59:36 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char	**get_path_list(char **env)
{
	int		i;
	char	*str;
	char	**arr;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			str = na_substr(env[i], 5, ft_strlen(env[i]) - 5);
			arr = na_split(str, ':');
			return (arr);
		}
		i++;
	}
	return (NULL);
}

void	handle_special_cases(char **path_list, char **cmd)
{
	if (!ft_strcmp(cmd[0], "."))
	{
		ft_putstr_fd("Leetshell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		exit(2);
	}
	if (!ft_strcmp(cmd[0], "..") && path_list
		&& path_list[0] && ft_strcmp(path_list[0], ""))
	{
		ft_putstr_fd("Leetshell: ..: command not found\n", 2);
		exit(127);
	}
	if ((path_list && path_list[0] && ft_strcmp(path_list[0], "")
			&& ft_strchr(cmd[0], '/')) || !path_list || !path_list[0]
		|| !ft_strcmp(path_list[0], ""))
		is_it_dir(cmd[0]);
}
