/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:46 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/05 17:56:30 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

void	up_env(t_env **env_list)
{
	char	pwd[PATH_MAX];
	char	*oldpwd;
	t_env	*tmp;

	tmp = *env_list;
	getcwd(pwd, PATH_MAX);
	oldpwd = NULL;
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
}

int	run_cd(char **argv, t_env **env_list)
{
	struct stat	sb;

	if (argv[2])
	{
		if (access(argv[2], F_OK) != 0)
		{
			printf("Executable: cd: %s: No such file or directory\n", argv[2]);
			return (1);
		}
		if (stat(argv[2], &sb) == 0 && (sb.st_mode & 0170000) == 0040000)
		{
			chdir(argv[2]);
			up_env(env_list);
		}
		else
		{
			printf("Executable: cd: %s: Not a directory\n", argv[2]);
			return (1);
		}
	}
	return (0);
}
