/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:12:50 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/23 09:04:26 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char	*build_target_path(int dotdots, const char *component, t_stash *stash)
{
	char	*pwd;
	char	*new_path;

	if (!stash || !stash->pwd_backup)
		return (NULL);
	pwd = na_strdup(stash->pwd_backup);
	new_path = na_strdup(pwd);
	if (!new_path)
		return (NULL);
	new_path = handle_dotdots(new_path, dotdots);
	if (!new_path)
		return (NULL);
	new_path = handle_component(new_path, component);
	return (new_path);
}

char	*handle_component_case(int dotdots, t_stash *stash)
{
	char	*target;

	target = build_target_path(dotdots, NULL, stash);
	return (target);
}

char	*process_components(const char *path, int dotdots,
t_stash *stash, char *component)
{
	char	*current_path;
	char	*target;
	int		start;
	int		end;

	current_path = NULL;
	start = 0;
	end = 0;
	while (component)
	{
		target = build_target_path(dotdots, component, stash);
		if (!target)
			return (NULL);
		if (access(target, F_OK) == 0)
			current_path = target;
		else
			break ;
		start = end;
		if (!path[start])
			break ;
		component = get_next_component(path, &start, &end);
		dotdots = 0;
	}
	return (current_path);
}
