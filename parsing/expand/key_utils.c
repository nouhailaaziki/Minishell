/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:05:05 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/12 16:52:11 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char	*find_a_key(char *origin, int *quote, int *key_len, int *pos)
{
	int		i;
	char	*dollar;

	i = 0;
	while (origin[i] && origin[i] != '$')
		i++;
	if (!origin[i] || !origin[i + 1] || !is_valid_key(origin[i + 1]))
		return (NULL);
	check_quote(origin, &origin[i], quote);
	dollar = &origin[i];
	*pos = i;
	i = 1;
	if (is_special_param(dollar[i]))
		i++;
	else
	{
		while (dollar[i] && (ft_isalnum(dollar[i]) || dollar[i] == '_'))
			i++;
	}
	dollar = ft_substr(dollar, 0, i);
	if (!dollar)
		return (NULL);
	*key_len = i;
	return (dollar);
}

t_var	*create_key(char *origin, int *quote, int *pos)
{
	char	*dollar;
	t_var	*key;
	int		key_len;
	int		relative_pos;

	key_len = 0;
	relative_pos = 0;
	dollar = find_a_key(origin, quote, &key_len, pos);
	if (!dollar)
		return (NULL);
	key = ft_calloc(1, sizeof(t_var));
	if (!key)
	{
		free(dollar);
		return (NULL);
	}
	key->key = dollar;
	key->key_len = key_len;
	key->expandable = *quote;
	return (key);
}

void	find_all_keys(char *str, t_var **keys)
{
	int		pos;
	int		relative_pos;
	t_var	*key;
	int		quote;

	quote = 0;
	pos = 0;
	if(!str )
		return ;
	while (str && str[pos])
	{
		relative_pos = 0;
		key = create_key(&str[pos], &quote, &relative_pos);
		if (!key)
			break ;
		link_nodes(keys, key);
		pos += relative_pos + key->key_len;
	}
}

void	ft_copy_keys(char **dest, t_var *current)
{
	if (current->expandable != '\'' && current->value)
	{
		ft_memcpy(*dest, current->value, current->value_len); // ? you changed here last
		*dest += current->value_len;
	}
	else
	{
		ft_memcpy(*dest, current->key, current->key_len);
		*dest += current->key_len;
	}
}

void	expand_a_key(t_var *current, t_env **env, int stash_status)
{
	char	*value;

	if (current->key && !ft_strcmp(current->key,"$?"))
		current->value = ft_itoa(stash_status);
	else
	{
		value = get_env_value(env, &(current->key[1]));
		if (!value)
			current->value = ft_strdup("");
		else
			current->value = ft_strdup(value);
	}
}
