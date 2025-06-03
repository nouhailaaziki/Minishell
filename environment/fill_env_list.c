/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:12:51 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/03 09:47:24 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

void	add_env_var(t_env **env_list, char *key)
{
	t_env	*tmp;
	t_env	*node;

	node = nalloc(sizeof(t_env));
	node->key = na_strdup(key);
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
	char	*key[4];
	int		found;
	int		i;

	1 && (key[0] = "PWD", key[1] = "OLDPWD", key[2] = "SHLVL");
	1 && (key[3] = "PATH", found = 0, tmp = *env_list);
	while (tmp)
	{
		i = 0;
		while (i < 4)
		{
			if (!ft_strcmp(tmp->key, key[i]))
			{
				found = 1;
				break ;
			}
			i++;
		}
		if (!found)
		add_env_var(env_list, key[i - 1]);
		tmp = tmp->next;
	}
}

void	upp_shlvl(t_env *node, int nbr)
{
	if (nbr == 999)
		node->value = na_strdup("");
	else if (nbr < 0)
		node->value = na_strdup("0");
	else if (nbr > 999)
		node->value = na_strdup("1");
	else
	{
		nbr += 1;
		node->value = na_strdup(na_itoa(nbr));
	}
}

t_env	*env_node(char *envp)
{
	t_env	*node;
	char	*sign;
	size_t	key_len;

	sign = ft_strchr(envp, '=');
	if (!sign)
		return (NULL);
	key_len = sign - envp;
	node = nalloc(sizeof(t_env));
	node->key = na_substr(envp, 0, key_len);
	if (!strcmp(node->key, "SHLVL"))
		upp_shlvl(node, ft_atoi(sign + 1));
	else
		node->value = na_strdup(sign + 1);
	node->next = NULL;
	return (node);
}

void	build_env(t_env **env_list, char **envp)
{
	t_env	*current;
	t_env	*new;

	while (*envp)
	{
		new = env_node(*envp);
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
