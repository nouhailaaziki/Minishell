/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:46 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/18 08:09:33 by noaziki          ###   ########.fr       */
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
	t_env *tmp;

	tmp = *env_list;
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			break ;
		tmp = tmp->next;
	}
	return (tmp->value);
}

int	cd(char **cmd, t_env **env_list)
{
	struct stat	sb;
	char 		*path;

	if (!cmd[1])
	{
		path = get_env_value(env_list, "HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
		chdir(path);
	}
	else
	{
		if (access(cmd[1], F_OK) != 0)
		{
			printf("L33tShell: cd: %s: No such file or directory\n", cmd[2]);
			return (1);
		}
		if (stat(cmd[1], &sb) == 0 && (sb.st_mode & 0170000) == 0040000)
		{
			chdir(cmd[1]);
			refresh_pwd(env_list);
		}
		else
		{
			printf("L33tShell: cd: %s: Not a directory\n", cmd[2]);
			return (1);
		}
	}
	return (0);
}
