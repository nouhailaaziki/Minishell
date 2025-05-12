/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:25:04 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/11 11:23:58 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/launchpad.h"

int	run_env(t_env **env_list)
{
	while (*env_list)
	{
		if ((*env_list)->value)
		{
			printf("%s=", (*env_list)->key);
			printf("%s\n", (*env_list)->value);
		}
		(*env_list) = (*env_list)->next;
	}
	return (0);
}
