/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:03:12 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/07 21:41:06 by noaziki          ###   ########.fr       */
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

int	expand_keys(t_var **head, t_env **env, int stash_status, int *keys_len)
{
	t_var	*current;
	char	*value;
	int		value_len;

	value_len = 0;
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
			value_len += current->value_len;
		}
		current = current->next;
	}
	return (value_len);
}

static char	*remove_quotes(char *str)
{
    char	*new_str;
    int		j;
    char	quote;

	j =0;
    if (!str)
        return (NULL);
    new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
    if (!new_str)
        return (NULL);
    while (*str)
    {
        if (*str == '\'' || *str == '\"')
        {
            quote = *str++;
            while (*str && *str != quote)
                new_str[j++] = *str++;
            if (*str == quote)
                (*str)++;
        }
        else
            new_str[j++] = *str++;
    }
    return (new_str);
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
		find_all_keys(cmd[i], &keys);
		if (!keys)
		{
		new_cmd = remove_quotes(cmd[i]);
		if (new_cmd)
		{
			free(cmd[i]);
			cmd[i] = new_cmd;
		}
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
		new_cmd = remove_quotes(cmd[i]);
        if (new_cmd)
        {
            free(cmd[i]);
            cmd[i] = new_cmd;
        }
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

// void expand_quotes(char **cmd)
// {

// }
