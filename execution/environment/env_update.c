/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:51:24 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/05 12:51:54 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

t_env	*create_node(char *argv, size_t key_len, char *sign)
{
	t_env	*node;

	node = nalloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (argv[key_len - 1] == '+')
		key_len--;
	node->key = na_substr(argv, 0, key_len);
	if (sign)
		node->value = na_strdup(sign + 1);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

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
