/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:46 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/13 11:15:00 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/launchpad.h"

void	refresh_pwd(t_env **env_list)
{
	char	pwd[PATH_MAX];
	char	*oldpwd;
	t_env	*tmp;

	1 && (tmp = *env_list, oldpwd = NULL);
	getcwd(pwd, PATH_MAX);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			oldpwd = ft_strdup(tmp->value);
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		else if (ft_strcmp(tmp->key, "OLDPWD") == 0 && oldpwd)
		{
			free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
		}
		tmp = tmp->next;
	}
	free(oldpwd);
}

int	run_cd(char **argv, t_env **env_list)
{
	struct stat	sb;

	if (argv[2])
	{
		if (access(argv[2], F_OK) != 0)
		{
			printf("minishell: cd: %s: No such file or directory\n", argv[2]);
			return (1);
		}
		if (stat(argv[2], &sb) == 0 && (sb.st_mode & 0170000) == 0040000)
		{
			chdir(argv[2]);
			refresh_pwd(env_list);
		}
		else
		{
			printf("minishell: cd: %s: Not a directory\n", argv[2]);
			return (1);
		}
	}
	return (0);
}
