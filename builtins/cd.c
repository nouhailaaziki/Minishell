/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:46 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/02 12:28:11 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

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

int	cd(char **cmd, t_env **env_list)
{
	struct stat	sb;

	if (cmd[1])
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
