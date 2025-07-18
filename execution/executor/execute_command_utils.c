/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:58:23 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/16 00:07:08 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	is_full_of_points(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

void	remove_full_of_points(char **arr)
{
	int	i;

	i = na_arrlen(arr);
	while (i > 0 && is_full_of_points(arr[i - 1]))
	{
		arr[i - 1] = NULL;
		i--;
	}
}

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
			remove_full_of_points(arr);
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
		ft_putendl_fd("Leetshell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		exit(2);
	}
	if (!ft_strcmp(cmd[0], "..") && path_list
		&& path_list[0] && ft_strcmp(path_list[0], ""))
	{
		ft_putendl_fd("Leetshell: ..: command not found", 2);
		exit(127);
	}
	if ((path_list && path_list[0] && ft_strcmp(path_list[0], "")
			&& ft_strchr(cmd[0], '/')) || !path_list || !path_list[0]
		|| !ft_strcmp(path_list[0], ""))
		is_it_dir(cmd[0]);
}
