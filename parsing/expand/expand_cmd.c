/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:03:12 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/09 16:50:55 by yrhandou         ###   ########.fr       */
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

void expand_a_key(t_var *current, t_env **env, int stash_status)
{
	char	*value;

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
}


void	expand_keys(t_var **keys, t_env **env, int stash_status, int *keys_len, int *values_len)
{
	t_var	*current;

	if(!keys || !*keys)
		return ;
	current = *keys;
	while (current)
	{
		if (current->expandable != '\'')
		{
			*keys_len += current->key_len;
			expand_a_key(current, env,stash_status);
			current->value_len = ft_strlen(current->value);
			*values_len += current->value_len;
		}
		current = current->next;
	}
}

char *expand_vars(t_var **keys, char **old_cmd, t_env **env ,int stash_status)
{
	int		values_len;
	int		keys_len;
	int 	alloc_len;
	char	*new_cmd;

	keys_len = 0;
	values_len = 0;
	*keys = NULL;
	find_all_keys(old_cmd[0], keys);
	expand_keys(keys, env, stash_status, &keys_len, &values_len);
	alloc_len = values_len - keys_len;
	expand_quotes(old_cmd, alloc_len, &new_cmd);
	return new_cmd;
}

void	update_cmd(char *origin, t_var **keys, char **destination)
{
	t_var	*current;
	char	*dest;
	char	*tmp;
	int		i;

	i = 0;
	current = *keys;
	dest = *destination;
	tmp = *destination;
	while (origin[i])
	{
		if (origin[i] == '$' && current && current->key
			&& !ft_strncmp(&origin[i], current->key, current->key_len))
		{
			ft_copy_keys(&dest, current);
			i += current->key_len;
			current = current->next;
		}
		else
			*dest++ = origin[i++];
	}
	*dest = '\0';
	*destination = tmp;
	free(origin);
	free_keys(keys);
}

int is_empty_values(t_var * keys)
{
	while(keys)
	{
		if(keys->value != NULL)
			return 0;
		keys = keys->next;
	}
	return 1;
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
			new_cmd = expand_vars(&keys, &cmd[i], env,stash_status);
			// free(cmd[i]);
			// cmd[i] = new_cmd;
			// free(cmd[i]);// cmd[i] = ft_strdup(new_cmd); // * shit that amine changed are from here look it up
			if(keys && !is_empty_values(keys))
				update_cmd(ft_strdup(new_cmd), &keys, &new_cmd); // ! double free becuase keys
			free(cmd[i]);
			cmd[i] = new_cmd;
		i++;
	}
}
