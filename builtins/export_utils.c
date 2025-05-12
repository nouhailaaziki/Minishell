/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:09:27 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/11 11:24:16 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/launchpad.h"

void	swap_env(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
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

t_env	*create_node(char *argv, size_t key_len, char *sign)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (argv[key_len - 1] == '+')
		key_len--;
	node->key = ft_strndup(argv, key_len);
	if (sign)
		node->value = ft_strdup(sign + 1);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	handle_argument(t_env **env_list, char *argv)
{
	int		j;
	int		n;
	char	*str;

	j = 0;
	while (argv[j] && argv[j] != '=')
		j++;
	if (j > 0 && argv[j - 1] == '+' && argv[j] == '=')
		j--;
	str = ft_substr(argv, 0, j);
	if (!str)
		return ;
	check_validity(str, "export");
	n = j + 1;
	if (argv[j] == '+' && j > 0 && argv[j + 1] && argv[j + 1] == '=')
		add_value(env_list, argv, str);
	else if (argv[j] == '=' || !argv[j])
		update_env(env_list, argv, str, n);
	free (str);
}
