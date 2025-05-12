/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:52:55 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/12 15:51:33 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/launchpad.h"

void	free_env_list(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free((*env));
		*env = tmp;
	}
}
