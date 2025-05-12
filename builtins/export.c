/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:00:55 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/11 11:24:23 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/launchpad.h"

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
			new_val = ft_strjoin(tmp->value, sign + 1);
			if (!new_val)
				return ;
			free(tmp->value);
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
			new_val = ft_substr(argv, start, len);
			if (!new_val)
				return ;
			free(tmp->value);
			tmp->value = new_val;
			i = 1;
		}
		tmp = tmp->next;
	}
	if (i == 0)
		add_node(env_list, argv);
}

void	print_env(t_env **env_list)
{
	t_env	*tmp;

	sort_env_list(env_list);
	tmp = *env_list;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

int	run_export(int argc, char **argv, t_env **env_list)
{
	int	i;

	i = 2;
	(void)argc;
	if (argc == 2)
		print_env(env_list);
	while (argv[i])
	{
		handle_argument(env_list, argv[i]);
		i++;
	}
	return (0);
}
