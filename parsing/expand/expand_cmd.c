/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:03:12 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/07 15:38:50 by yrhandou         ###   ########.fr       */
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

void	update_cmd(char *origin, t_var *keys, char **destination)
{
	t_var	*current;
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	current = keys;
	dest = *destination;
	while (origin[i])
	{
		if (origin[i] == '$' && current->key
			&& !ft_strncmp(&origin[i], current->key, current->key_len))
		{
			ft_copy_keys(&dest[j], &j, current);
			i += current->key_len;
			current = current->next;
		}
		else
			dest[j++] = origin[i++];
	}
	dest[j] = '\0' ;
}

void	expand_cmd(char **cmd, t_env **env, int stash_status)
{
	int		i;
	int		value_len;
	int		keys_len;
	t_var	*keys;
	char	*new_cmd;

	if (!cmd || !*cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		find_all_keys(cmd[i], &keys, stash_status);
		if (!keys)
		{
			i++;
			continue ;
		}
		keys_len = 0;
		value_len = expand_keys(&keys, env, stash_status, &keys_len);
		new_cmd = ft_calloc(ft_strlen(cmd[i]) + value_len - keys_len \
		+ 1, sizeof(char));
		if (!new_cmd)
		{
			free_keys(&keys);
			return ;
		}
		update_cmd(cmd[i], keys, &new_cmd);
		free(cmd[i]);
		cmd[i] = new_cmd;
		free_keys(&keys);
		i++;
	}
}

void	quote_expander(t_token **head)
{
	t_token	*current;
	int		position;
	int		i;
	char	quote;
	char	*expanded_token;

	i = 0;
	position = 0;
	current = *head;
	while (current)
	{
		if (ft_strchr(current->value, '\"') == NULL && \
		ft_strchr(current->value, '\'') == NULL)
		{
			current = current->next;
			continue ;
		}
		expanded_token = ft_calloc(ft_strlen(current->value) + 1, sizeof(char));
		if (!expanded_token)
			return (free_tokens(head), ft_putendl_fd("MALLOC FAILURE", 2));
		while (current->value[i])
		{
			quote = ft_isquote(current->value[i]);
			if (quote != '\0')
			{
				i++;
				while (current->value[i] && current->value[i] != quote)
					expanded_token[position++] = current->value[i++];
				if (current->value[i] == quote)
					i++;
			}
			else
				expanded_token[position++] = current->value[i++];
		}
		if (expanded_token)
		{
			free(current->value);
			current->value = expanded_token;
		}
		current = current->next;
	}
}
