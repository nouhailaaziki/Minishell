/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:00:55 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/26 10:54:33 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	add_node(t_env **env_list, char *argv)
{
	t_env	*tmp;
	t_env	*node;
	char	*sign;
	size_t	key_len;

	sign = ft_strchr(argv, '=');
	if (sign)
		key_len = sign - argv;
	else
		key_len = ft_strlen(argv);
	node = create_node(argv, key_len, sign);
	if (!*env_list)
	{
		*env_list = node;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	add_value(t_env	**env_list, char *argv, char *key)
{
	t_env	*tmp;
	int		i;
	char	*sign;
	char	*new_val;

	tmp = *env_list;
	i = 0;
	sign = ft_strchr(argv, '=');
	if (!sign)
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			new_val = na_strjoin(tmp->value, sign + 1);
			if (!new_val)
				return ;
			tmp->value = new_val;
			i = 1;
		}
		tmp = tmp->next;
	}
	if (i == 0)
		add_node(env_list, argv);
}

void	update_env(t_env **env_list, char *argv, char *key, int start)
{
	t_env	*tmp;
	int		i;
	int		len;
	char	*new_val;

	len = ft_strlen(argv) - start;
	tmp = *env_list;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			new_val = na_substr(argv, start, len);
			if (!new_val)
				return ;
			tmp->value = new_val;
			i = 1;
		}
		tmp = tmp->next;
	}
	if (i == 0)
		add_node(env_list, argv);
}

void	print_env(t_env **env_list, t_stash *stash)
{
	t_env	*tmp;

	sort_env_list(env_list);
	tmp = *env_list;
	while (tmp)
	{
		if (stash->path_flag == 1 && !ft_strcmp(tmp->key, "PATH"))
			tmp = tmp->next;
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

	i = 1;
	len = ft_arrlen(cmd);
	if (len == 1)
		print_env(env_list, stash);
	while (cmd[i])
	{
		handle_argument(env_list, cmd[i]);
		i++;
	}
	return (0);
}
