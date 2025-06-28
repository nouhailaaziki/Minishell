/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:44:34 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/28 11:20:35 by noaziki          ###   ########.fr       */
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
