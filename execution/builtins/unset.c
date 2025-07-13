/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:00:49 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/12 12:47:37 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	check_validity(char	*argv, char *initial, char *cmd)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!((argv[i] >= 'a' && argv[i] <= 'z')
				|| (i > 0 && argv[i] >= '0' && argv[i] <= '9')
				|| argv[i] == '_' || (argv[i] >= 'A' && argv[i] <= 'Z')))
		{
			(ft_putstr_fd("L33tShell: ", 2), ft_putstr_fd(cmd, 2));
			(ft_putstr_fd(": `", 2), ft_putstr_fd(initial, 2));
			ft_putendl_fd("': not a valid identifier", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	del_node(t_env **curr, t_env **env_list, char *argv, t_env **prev)
{
	t_env	*tmp;

	if (ft_strcmp((*curr)->key, argv) == 0)
	{
		tmp = (*curr)->next;
		(*curr)->key = NULL;
		(*curr)->value = NULL;
		*curr = NULL;
		if (*prev)
			(*prev)->next = tmp;
		else
			*env_list = tmp;
		*curr = tmp;
	}
	else
	{
		*prev = *curr;
		*curr = (*curr)->next;
	}
}

int	unset(t_env **env_list, char **cmd, t_stash *stash)
{
	t_env	*curr;
	t_env	*prev;
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (check_validity(cmd[i], cmd[i], "unset"))
		{
			stash->return_status = 1;
			i++;
			continue ;
		}
		curr = *env_list;
		prev = NULL;
		while (curr)
			del_node(&curr, env_list, cmd[i], &prev);
		i++;
	}
	return (stash->return_status);
}
