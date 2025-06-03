/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:25:04 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/03 09:46:42 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	env(t_env *env_list)
{
	if (!env_list)
		ft_putstr_fd("L33tShell: env: No such file or directory\n", 2);
	while (env_list)
	{
		if (env_list->value && env_list->value[0])
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	return (0);
}
