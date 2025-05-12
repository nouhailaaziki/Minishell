/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:29:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/11 11:24:32 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/launchpad.h"

int	run_pwd(t_env **env_list)
{
	while (*env_list)
	{
		if ((ft_strcmp((*env_list)->key, "PWD")) == 0)
			ft_putstr_fd((*env_list)->value, 1);
		*env_list = (*env_list)->next;
	}
	return (0);
}
