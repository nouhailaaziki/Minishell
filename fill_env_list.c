/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:12:51 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/02 16:48:15 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

t_env	*create_env_node(char *envp)
{
	t_env	*node;
	char	*sign;
	size_t	key_len;

	sign = strchr(envp, '=');
	if (!sign)
		return (NULL);
	key_len = sign - envp;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = strndup(envp, key_len);
	node->value = strdup(sign + 1);
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
}
