/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:46 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/27 11:55:41 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	refresh_oldpwd(t_env **env_list, char *oldpwd)
{
	t_env	*tmp;

	tmp = *env_list;
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
			tmp->value = na_strdup(pwd);
			if (!tmp->value)
				return (perror("malloc"));
		}
		tmp = tmp->next;
	}
	refresh_oldpwd(env_list, oldpwd);
	free(pwd);
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
		refresh_pwd(env_list);
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
