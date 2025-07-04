/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:09:27 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/04 09:51:55 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	swap_env(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void	sort_env_list(t_env **env_list)
{
	t_env	*tmp;
	int		swapped;

	if (!env_list || !*env_list)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		tmp = *env_list;
		while (tmp && tmp->next)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				swap_env(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
	}
}

int	export_error(char *cmd)
{
	ft_putstr_fd("L33tShell: export: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	handle_no_equal(t_env **env_list, char *cmd, char *str)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			return (0);
		tmp = tmp->next;
	}
	add_node(env_list, cmd);
	return (0);
}

int	handle_argument(t_env **env_list, char *cmd)
{
	int		j;
	char	*str;

	j = 0;
	while (cmd[j] && cmd[j] != '=')
		j++;
	if (j == 0 || (j == 0 && cmd[j] == '+') || (j > 0 && cmd[j - 1] == '+'
			&& cmd[j] == '=' && j--))
		return (export_error(cmd));
	str = na_substr(cmd, 0, j);
	if (!str)
		return (perror("malloc"), 1);
	if (check_validity(str, cmd, "export"))
		return (1);
	if (cmd[j] == '+' && j > 0 && cmd[j + 1] && cmd[j + 1] == '=')
		add_value(env_list, cmd, str);
	else if (cmd[j] == '=')
		update_env(env_list, cmd, str, j + 1);
	else
		return (handle_no_equal(env_list, cmd, str));
	return (0);
}
