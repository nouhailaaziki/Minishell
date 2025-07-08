/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:03:12 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/08 16:25:26 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char	*expand_special_param(char c, int stash_status)
{
	pid_t	my_pid;

	if (c == '?')
		return (ft_itoa(stash_status));
	if (ioctl(STDIN_FILENO, TIOCGPGRP, &my_pid) == -1)
	{
		perror("ioctl");
		exit(1);
	}
	return (ft_itoa(my_pid));
}

void	expand_keys(t_var **head, t_env **env, int stash_status, int *keys_len, int *values_len)
{
	t_var	*current;
	char	*value;

	current = *head;
	while (current)
	{
		if (current->expandable != '\'')
		{
			*keys_len += current->key_len;
			if (current->key && is_special_param(current->key[1]))
				current->value = expand_special_param(current->key[1], stash_status);
			else
			{
				value = get_env_value(env, &(current->key[1]));
				if (!value)
					current->value = ft_strdup("");
				else
					current->value = ft_strdup(value);
			}
			current->value_len = ft_strlen(current->value);
			*values_len += current->value_len;
		}
		current = current->next;
	}
}

char *expand_vars(t_var **keys, char **old_cmd, t_env **env, int stash_status)
{
	int		values_len;
	int		keys_len;
	int 	alloc_len;
	char	*new_cmd;

	keys_len = 0;
	values_len = 0;
	*keys = NULL;
	find_all_keys(old_cmd[0], keys);
	if (!keys || !*keys)
	{
		expand_quotes(old_cmd, &new_cmd);
		return (new_cmd);
	}
	expand_keys(keys, env, stash_status, &keys_len, &values_len);
	alloc_len = ft_strlen(old_cmd[0]) - keys_len + values_len;
	new_cmd = ft_calloc(alloc_len + 1, sizeof(char));
	if (!new_cmd)
	{
		free_keys(keys);
		return NULL;
	}
	return new_cmd;
}

void	update_cmd(char **origin, t_var **keys, char **destination)
{
	t_var	*current;
	char	*dest;
	int		i;

	i = 0;
	current = *keys;
	dest = *destination;
	while ((*origin)[i])
	{
		if ((*origin)[i] == '$' && current && current->key
			&& !ft_strncmp(&(*origin)[i], current->key, current->key_len))
		{
			ft_copy_keys(&dest, 0, current);
			i += current->key_len;
			current = current->next;
		}
		else
			*dest++ = (*origin)[i++];
	}
	*dest = '\0' ;
	free(*origin);
	*origin = *destination;
	free_keys(keys);
}
void	expand_cmd(char **cmd, t_env **env, int stash_status)
{
	int		i;
	t_var	*keys;
	char	*new_cmd;

	if (!cmd || !*cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		new_cmd = expand_vars(&keys, &cmd[i], env, stash_status);
		if (!keys)
		{
			free(cmd[i]);
			cmd[i] = new_cmd;
		}
		else
			update_cmd(&cmd[i], &keys, &new_cmd);
		i++;
	}
}
