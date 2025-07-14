/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:09:27 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/14 15:11:24 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	export_error(char *cmd)
{
	ft_putstr_fd("L33tShell: export: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd("': not a valid identifier", 2);
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

int	handle_plus_equal(t_env **env_list, char *cmd, int j)
{
	char	*str;

	if (j == 0)
		return (export_error(cmd));
	str = na_substr(cmd, 0, j);
	if (!str)
		return (perror("malloc"), 1);
	if (check_validity(str, cmd, "export"))
		return (1);
	add_value(env_list, cmd, str);
	return (0);
}

int	handle_equal(t_env **env_list, char *cmd, int j)
{
	char	*str;

	str = na_substr(cmd, 0, j);
	if (!str)
		return (perror("malloc"), 1);
	if (check_validity(str, cmd, "export"))
		return (1);
	update_env(env_list, cmd, str, j + 1);
	return (0);
}

int	handle_argument(t_env **env_list, char *cmd)
{
	int		j;
	char	*str;

	j = 0;
	if (cmd[0] == '=' || cmd[0] == '+' || cmd[0] == '\0')
		return (export_error(cmd));
	while (cmd[j] && cmd[j] != '=' && cmd[j] != '+')
		j++;
	if (cmd[j] == '+' && cmd[j + 1] == '=')
		return (handle_plus_equal(env_list, cmd, j));
	else if (cmd[j] == '+' && cmd[j + 1] != '=')
		return (puterror("L33tShell: ", "export: ", \
		cmd, ": not a valid identifier"));
	else if (cmd[j] == '=')
		return (handle_equal(env_list, cmd, j));
	else
	{
		str = na_substr(cmd, 0, j);
		if (!str)
			return (perror("malloc"), 1);
		if (check_validity(str, cmd, "export"))
			return (1);
		return (handle_no_equal(env_list, cmd, str));
	}
}
