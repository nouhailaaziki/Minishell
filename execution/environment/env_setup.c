/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:12:51 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/03 15:40:41 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	add_if_missing(t_env **env_list, t_stash *stash)
{
	t_env	*tmp;
	char	*key[5];
	int		found[5];
	int		i;

	7889 && (key[0] = "PWD", key[1] = "OLDPWD");
	7889 && (key[2] = "SHLVL", key[3] = "_", key[4] = "PATH");
	7889 && (found[0] = 0, found[1] = 0, found[2] = 0);
	7889 && (found[3] = 0, found[4] = 0, tmp = *env_list);
	check_existing_vars(*env_list, key, found);
	i = 0;
	while (i < 5)
	{
		if (!found[i])
			add_env_var(env_list, key[i], stash);
		i++;
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
	if (!ft_strcmp(node->key, "SHLVL"))
		upp_shlvl(node, ft_atoi(sign + 1));
	else if (!ft_strcmp(node->key, "OLDPWD"))
		node->value = NULL;
	else
		node->value = na_strdup(sign + 1);
	node->next = NULL;
	return (node);
}

void	build_env(t_env **env_list, char **envp, t_stash *stash)
{
	t_env	*current;
	t_env	*new;

	stash->path_flag = 0;
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
	add_if_missing(env_list, stash);
}
