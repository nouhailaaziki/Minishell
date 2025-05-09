/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:12:51 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/09 14:25:55 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

void	add_key(t_env **env_list, char *key)
{
	t_env	*tmp;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->key = ft_strdup(key);
	if (!node->key)
		return ;
	node->value = NULL;
	node->next = NULL;
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

void	check_list(t_env **env_list)
{
	t_env	*tmp;
	char	*key[1];
	int		i;
	int		found;

	key[0] = "OLDPWD";
	i = 0;
	found = 0;
	while (i < 1)
	{
		tmp = *env_list;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, key[i]) == 0)
			{
				found = 1;
				break ;
			}
			tmp = tmp->next;
		}
		if (!found)
			add_key(env_list, key[i]);
		i++;
	}
}

t_env	*create_env_node(char *envp)
{
	t_env	*node;
	char	*sign;
	size_t	key_len;

	sign = ft_strchr(envp, '=');
	if (!sign)
		return (NULL);
	key_len = sign - envp;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = strndup(envp, key_len);
	node->value = ft_strdup(sign + 1);
	node->next = NULL;
	return (node);
}

void	fill_env_list(char **envp, t_env **env_list)
{
	t_env	*current;
	t_env	*new;

	while (*envp)
	{
		new = create_env_node(*envp);
		if (!new)
			return ;
		if (!*env_list)
			*env_list = new;
		else
		{
			current = *env_list;
			while (current->next)
			{
				current = current->next;
			}
			current->next = new;
		}
		envp++;
	}
	check_list(env_list);
}
