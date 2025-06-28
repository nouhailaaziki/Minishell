/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:07:56 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/27 12:11:06 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char	*add_env_value(char *key, t_stash *stash)
{
	char	*pwd;

	if (!ft_strcmp(key, "PWD"))
	{
		pwd = getcwd(0, 0);
		if (!pwd)
			return (NULL);
		return (pwd);
	}
	else if (!ft_strcmp(key, "PATH"))
	{
		stash->path_flag = 1;
		return ("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	}
	else if (!ft_strcmp(key, "SHLVL"))
		return ("1");
	else if (!ft_strcmp(key, "_"))
		return ("/usr/bin/env");
	return (NULL);
}

void	add_env_var(t_env **env_list, char *key, t_stash *stash)
{
	t_env	*tmp;
	t_env	*node;

	node = nalloc(sizeof(t_env));
	node->key = na_strdup(key);
	if (!ft_strcmp(key, "OLDPWD"))
		node->value = NULL;
	else
		node->value = na_strdup(add_env_value(key, stash));
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

void	check_existing_vars(t_env *env_list, char **keys, int *found)
{
	t_env	*tmp;
	int		i;

	tmp = env_list;
	while (tmp)
	{
		i = 0;
		while (i < 5)
		{
			if (!ft_strcmp(tmp->key, keys[i]))
				found[i] = 1;
			i++;
		}
		tmp = tmp->next;
	}
}
