/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:54:36 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/04 09:24:15 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char	*process_cd_path(const char *path, t_stash *stash)
{
	int		dotdots;
	int		i;
	int		start;
	char	*component;

	i = 0;
	if (!path || !stash || !stash->pwd_backup)
		return (NULL);
	dotdots = count_leading_dotdots(path);
	while (path[i] && (path[i] == '.' || path[i] == '/'))
		i++;
	start = i;
	if (path[start] == '/')
		start++;
	component = get_next_component(path, &start, &i);
	if (!component && dotdots > 0)
		return (handle_component_case(dotdots, stash));
	return (process_components(path, dotdots, stash, component));
}

int	handle_no_arg(t_env **env_list, t_stash *stash)
{
	char	*path;

	path = get_env_value(env_list, "HOME");
	if (!path)
		return (puterror(0, "cd: ", NULL, "HOME not set"));
	chdir(path);
	refresh_pwd(env_list, stash, NULL);
	return (0);
}

int	handle_path_access(char **path, char *arg, t_stash *stash)
{
	if (access(*path, F_OK) != 0)
	{
		if (process_cd_path(arg, stash))
			*path = process_cd_path(arg, stash);
		if (access(*path, F_OK) != 0)
			return (puterror(1, "cd: ", arg, \
			": No such file or directory"));
	}
	return (0);
}

int	handle_directory_check(char *path, char *arg, \
t_env **env_list, t_stash *stash)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && (sb.st_mode & 0170000) == 0040000)
	{
		if (chdir(path) == -1)
			return (puterror(1, "cd: ", arg, ": Permission denied"));
		refresh_pwd(env_list, stash, arg);
	}
	else
		return (puterror(1, "cd: ", arg, ": Not a directory"));
	return (0);
}

int	cd(char **cmd, t_env **env_list, t_stash *stash)
{
	char		*path;
	int			ret;

	if (!cmd[1])
		return (handle_no_arg(env_list, stash));
	path = na_strdup(cmd[1]);
	ret = handle_path_access(&path, cmd[1], stash);
	if (ret != 0)
		return (ret);
	return (handle_directory_check(path, cmd[1], env_list, stash));
}
