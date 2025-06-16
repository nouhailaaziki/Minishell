/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:00:49 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/09 08:07:22 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	check_validity(char	*argv, char *cmd)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!((argv[i] >= 'a' && argv[i] <= 'z')
				|| (i > 0 && argv[i] >= '0' && argv[i] <= '9')
				|| argv[i] == '_' || (argv[i] >= 'A' && argv[i] <= 'Z')))
		{
			printf("L33tShell: %s: `%s`: not a valid identifier\n", cmd, argv);
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
		free((*curr)->key);
		free((*curr)->value);
		free(*curr);
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

int	unset(t_env **env_list, char **cmd)
{
	t_env	*curr;
	t_env	*prev;
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (check_validity(cmd[i], "unset"))
		{
			i++;
			continue ;
		}
		curr = *env_list;
		prev = NULL;
		while (curr)
			del_node(&curr, env_list, cmd[i], &prev);
		i++;
	}
	return (0);
}
