/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:27:50 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/29 09:01:52 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char	**get_env_arr(t_env *env_list)
{
	int		i;
	int		len;
	char	**envp;
	t_env	*backup;

	1 && (len = 0, i = 0, envp = NULL, backup = env_list);
	while (env_list)
	{
		len++;
		env_list = env_list->next;
	}
	env_list = backup;
	envp = (char **)nalloc(((len + 1) * sizeof(char *)));
	while (env_list)
	{
		envp[i] = na_strjoin(env_list->key, "=");
		envp[i] = na_strjoin(envp[i], env_list->value);
		env_list = env_list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
