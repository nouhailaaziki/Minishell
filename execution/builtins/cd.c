/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:54:36 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/03 15:33:29 by noaziki          ###   ########.fr       */
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
		path = na_strdup(cmd[1]);
		if (access(path, F_OK) != 0)
		{
			if (process_cd_path(cmd[1], stash))
				path = process_cd_path(cmd[1], stash);
			if (access(path, F_OK) != 0)
				return (puterror(1, "cd: ", cmd[1], ": No such file or directory"));
		}
		if (stat(path, &sb) == 0 && (sb.st_mode & 0170000) == 0040000)
		{
			if (chdir(path) == -1)
				return (puterror(1, "cd: ", cmd[1], ": Permission denied"));
			refresh_pwd(env_list, stash, cmd[1]);
		}
		else
			return (puterror(1, "cd: ", cmd[1], ": Not a directory"));
	}
	return (0);
}
