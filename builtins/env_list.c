/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:12:51 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/11 16:48:00 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/launchpad.h"

void	add_env_var(t_env **env_list, char *key)
{
	t_env	*tmp;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return ;
	}
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

void	add_if_missing(t_env **env_list)
{
	t_env	*tmp;
	char	*key;
	int		found;

	key = "OLDPWD";
	found = 0;
	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			found = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!found)
		add_env_var(env_list, key);
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
	node->key = ft_strndup(envp, key_len);
	if (!node->key)
		return (free (node), NULL);
	node->value = ft_strdup(sign + 1);
	if (!node->value)
		return (free(node->key), free(node), NULL);
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
				current = current->next;
			current->next = new;
		}
		envp++;
	}
	add_if_missing(env_list);
}
