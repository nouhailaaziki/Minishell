/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:00:55 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/05 16:00:51 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	print_env_list(t_env **env_list, t_stash *stash)
{
	t_env	*tmp;

	sort_env_list(env_list);
	tmp = *env_list;
	while (tmp)
	{
		if (tmp && stash->path_flag == 1 && !ft_strcmp(tmp->key, "PATH"))
		{
			tmp = tmp->next;
			if (!tmp)
				break ;
		}
		if (tmp && tmp->value && ft_strcmp(tmp->key, "_"))
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		if (tmp && !tmp->value && ft_strcmp(tmp->key, "_"))
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

int	export(char **cmd, t_env **env_list, t_stash *stash)
{
	int	i;
	int	len;
	int	status;

	i = 1;
	status = 0;
	len = na_arrlen(cmd);
	if (len == 1)
		print_env_list(env_list, stash);
	while (cmd[i])
	{
		stash->return_status = handle_argument(env_list, cmd[i]);
		if (stash->return_status == 1)
			status = 1;
		i++;
	}
	stash->return_status = status;
	return (stash->return_status);
}
