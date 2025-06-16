/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:25:04 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/09 08:07:22 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

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
