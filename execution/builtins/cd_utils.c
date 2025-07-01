/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:44:34 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/30 23:19:47 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	refresh_oldpwd(t_env **env_list, char *oldpwd)
{
	t_env	*tmp;

	tmp = *env_list;
	if (!oldpwd)
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0 && oldpwd)
		{
			tmp->value = na_strdup(oldpwd);
			if (!tmp->value)
				return (perror("malloc"));
		}
		tmp = tmp->next;
	}
}

int	skip_points(char *path)
{
	int	i;
	
	i = 0;
	while (path && (!ft_strcmp(&path[i], ".") || !ft_strcmp(&path[i], "/")))
		i++;
	return (i);
}

char	*get_valid_path(int counter, t_stash *stash)
{
	char	*path;
	char	*new_path;
	int		i;

	i = 0;
	path = getcwd(0, 0);
	if (!path)
	{
		path = na_strdup(stash->pwd_backup);
		if (!path)
			return (NULL);
	}
	while(path[i])
		i++;
	i--;
	while (i > 0)
	{
		if (!ft_strcmp(&path[i], "/") && counter != 0)
			counter--;
		i--;
	}
	new_path = na_substr(path, 0, i);
	if (!new_path)
		return (NULL);
	return (new_path);
}

int	pathchr(char *path)
{
	int	len;
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	len = skip_points(path);
	if (len == 0)
		return (0);
	while (path[i] && i < len)
	{
		if (!ft_strcmp(&path[i], "."))
		{
			if (path[i + 1] && path[i - 1] 
				&& !ft_strcmp(&path[i + 1], ".") && !ft_strcmp(&path[i - 1], "/"))
			{
				if (path[i + 1] && !ft_strcmp(&path[i + 1], "/"))
					counter += 1;
			}
		}
		i++;
	}
	return (counter);
}