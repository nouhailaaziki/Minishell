/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:00:49 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/12 16:23:56 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/launchpad.h"

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
			printf("minishell: %s: `%s`: not a valid identifier\n", cmd, argv);
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

int	run_unset(t_env **env_list, char **argv)
{
	t_env	*curr;
	t_env	*prev;
	int		i;

	i = 2;
	while (argv[i])
	{
		if (check_validity(argv[i], "unset"))
		{
			i++;
			continue ;
		}
		curr = *env_list;
		prev = NULL;
		while (curr)
			del_node(&curr, env_list, argv[i], &prev);
		i++;
	}
	return (0);
}
