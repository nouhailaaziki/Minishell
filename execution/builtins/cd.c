/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:46 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/23 17:59:00 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	refresh_pwd(t_env **env_list)
{
	char	*pwd;
	char	*oldpwd;
	t_env	*tmp;

	1 && (tmp = *env_list, oldpwd = NULL);
	pwd = getcwd(0, 0);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			oldpwd = na_strdup(tmp->value);
			free(tmp->value);
			tmp->value = na_strdup(pwd);
		}
		else if (ft_strcmp(tmp->key, "OLDPWD") == 0 && oldpwd)
		{
			free(tmp->value);
			tmp->value = na_strdup(oldpwd);
		}
		tmp = tmp->next;
	}
	free(pwd);
	free(oldpwd);
}

char	*get_env_value(t_env **env_list, char *key)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	cd(char **cmd, t_env **env_list)
{
	struct stat	sb;
	char		*path;

	if (!cmd[1])
	{
		path = get_env_value(env_list, "HOME");
		if (!path)
			return (puterror(0, "cd: ", NULL, "HOME not set"));
		chdir(path);
	}
	else
	{
		if (access(cmd[1], F_OK) != 0)
			return (puterror(1, "cd: ", cmd[2], ": No such file or directory"));
		if (stat(cmd[1], &sb) == 0 && (sb.st_mode & 0170000) == 0040000)
		{
			chdir(cmd[1]);
			refresh_pwd(env_list);
		}
		else
			return (puterror(1, "cd: ", cmd[2], ": Not a directory"));
	}
	return (0);
}
