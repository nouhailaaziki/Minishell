/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:25:04 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/27 19:16:59 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	env(t_env *env_list, t_stash *stash)
{
	if (!env_list)
		ft_putstr_fd("L33tShell: env: No such file or directory\n", 2);
	while (env_list)
	{
		if (stash->path_flag == 1 && !ft_strcmp(env_list->key, "PATH"))
			env_list = env_list->next;
		if (env_list && (env_list->value || !ft_strcmp(env_list->value, "")))
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	return (0);
}
