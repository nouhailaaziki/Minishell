/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:09:27 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/28 08:44:16 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

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

int	export_error(char *cmd)
{
	ft_putstr_fd("L33tShell: export: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

void	handle_argument(t_env **env_list, char *cmd, t_stash *stash)
{
	int		j;
	int		n;
	char	*str;

	j = 0;
	while (cmd[j] && cmd[j] != '=')
		j++;
	if (j == 0)
		stash->return_status = export_error(cmd);
	if (j > 0 && cmd[j - 1] == '+' && cmd[j] == '=')
		j--;
	if (j == 0 && cmd[j] == '+')
		stash->return_status = export_error(cmd);
	str = na_substr(cmd, 0, j);
	if (!str)
		return ;
	if (check_validity(str, cmd, "export"))
		stash->return_status = 1;
	n = j + 1;
	if (cmd[j] == '+' && j > 0 && cmd[j + 1] && cmd[j + 1] == '=')
		add_value(env_list, cmd, str);
	else if (cmd[j] == '=' || !cmd[j])
		update_env(env_list, cmd, str, n);
}
