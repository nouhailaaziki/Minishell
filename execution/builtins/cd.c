/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:42:46 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/28 11:19:53 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	handle_failed_getcwd(t_env *pwd_node, t_stash *stash, char *cmd)
{
	pwd_node->value = na_strjoin(stash->pwd_backup, "/");
	if (!pwd_node->value)
		return (perror("malloc"));
	pwd_node->value = na_strjoin(pwd_node->value, cmd);
	if (!pwd_node->value)
		return (perror("malloc"));
	stash->pwd_backup = na_strdup(pwd_node->value);
	if (!pwd_node->value)
		return (perror("malloc"));
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories:", 2);
	ft_putstr_fd(" No such file or directory\n", 2);
}

char	*update_pwd_node(t_env *pwd_node, t_stash *stash, \
char *new_pwd, char *cmd)
{
	char	*oldpwd_val;

	oldpwd_val = na_strdup(pwd_node->value);
	if (new_pwd)
	{
		pwd_node->value = na_strdup(new_pwd);
		if (!pwd_node->value)
			perror("malloc");
	}
	else
		handle_failed_getcwd(pwd_node, stash, cmd);
	return (oldpwd_val);
}

void	refresh_pwd(t_env **env_list, t_stash *stash, char *cmd)
{
	char	*pwd;
	char	*oldpwd;
	t_env	*tmp;

	tmp = *env_list;
	oldpwd = NULL;
	pwd = getcwd(0, 0);
	if (pwd)
		stash->pwd_backup = na_strdup(pwd);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			oldpwd = update_pwd_node(tmp, stash, pwd, cmd);
			if (!oldpwd)
				perror("malloc");
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

int	cd(char **cmd, t_env **env_list, t_stash *stash)
{
	struct stat	sb;
	char		*path;

	if (!cmd[1])
	{
		path = get_env_value(env_list, "HOME");
		if (!path)
			return (puterror(0, "cd: ", NULL, "HOME not set"));
		chdir(path);
		refresh_pwd(env_list, stash, cmd[1]);
	}
	else
	{
		if (access(cmd[1], F_OK) != 0)
			return (puterror(1, "cd: ", cmd[2], ": No such file or directory"));
		if (stat(cmd[1], &sb) == 0 && (sb.st_mode & 0170000) == 0040000)
		{
			chdir(cmd[1]);
			refresh_pwd(env_list, stash, cmd[1]);
		}
		else
			return (puterror(1, "cd: ", cmd[2], ": Not a directory"));
	}
	return (0);
}
