/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:05:54 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/03 16:06:17 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	count_leading_dotdots(const char *path)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] == '.'
			&& (path[i + 2] == '/' || path[i + 2] == '\0'))
		{
			count++;
			i += 2;
			if (path[i] == '/')
				i++;
		}
		else
			break ;
	}
	return (count);
}

char	*get_next_component(const char *path, int *start, int *end)
{
	int	i;

	i = *start;
	while (path[i] == '/')
		i++;
	*start = i;
	while (path[i] && path[i] != '/')
		i++;
	*end = i;
	if (*start == *end)
		return (NULL);
	return (na_substr(path, *start, *end - *start));
}

char	*build_target_path(int dotdots, const char *component, t_stash *stash)
{
	char	*pwd;
	char	*new_path;
	char	*temp;
	char	*temp2;

	if (!stash || !stash->pwd_backup)
		return (NULL);
	pwd = stash->pwd_backup;
	new_path = na_strdup(pwd);
	if (!new_path)
		return (NULL);
	while (dotdots-- > 0)
	{
		temp = ft_strrchr(new_path, '/');
		if (!temp)
			return (NULL);
		*temp = '\0';
		if (temp == new_path)
			break;
	}
	if (component && *component)
	{
		temp = na_strjoin(new_path, "/");
		if (!temp)
			return (NULL);
		temp2 = na_strjoin(temp, component);
		new_path = temp2;
		if (!new_path)
			return (NULL);
	}
	return (new_path);
}

char	*process_cd_path(const char *path, t_stash *stash)
{
	int		dotdots;
	int		start;
	int		end;
	int		i;
	char	*current_path;
	char	*component;
	char	*target;

	i = 0;
	if (!path || !stash || !stash->pwd_backup)
		return (NULL);
	dotdots = count_leading_dotdots(path);
	while(path[i] && (path[i] == '.' || path[i] == '/'))
		i++;
	start = i;
	if (path[start] == '/')
		start++;
	current_path = NULL;
	end = 0;
	component = get_next_component(path, &start, &end);
	if (!component && dotdots > 0)
	{
		target = build_target_path(dotdots, NULL, stash);
			return (target);
	}
	while (component)
	{
		target = build_target_path(dotdots, component, stash);
		if (!target)
			return (NULL);
		if (access(target, F_OK) == 0)
			current_path = target;
		else
			break;
		start = end;
		if (!path[start])
			break;
		component = get_next_component(path, &start, &end);
		dotdots = 0;
	}
	return (current_path);
}
