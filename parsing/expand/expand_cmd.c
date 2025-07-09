/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:03:12 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/09 20:46:50 by yrhandou         ###   ########.fr       */
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
	new_cmd = ft_calloc(alloc_len +1, sizeof(char));
	if(!new_cmd)
	{
		free(*keys);
		return *old_cmd;
	}
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


int	get_size(char **arr){
	int	s = 0;
	if (!arr)
		return 0;
	while (arr[s])
		s++;
	return (s);
}

void	add_to_array(char ***arr, char *add)
{
	int	size = 0;
	char	**new;
	size = get_size(*arr);
	new = malloc(sizeof(char *) * (size + 2));
	if (!new)
		return ;
	int	i = 0;
	while (*arr && *arr[i])
	{
		new[i] = *arr[i];
		i++;
	}
	new[i++] = ft_strdup(add);
	new[i] = NULL;
	free_cmd(*arr);
	*arr = new;
}

void	skip_quote(char *str, int *i, char quote)
{
	while (str[*i] && str[*i] == quote)
		*i += 1;
	if (str[*i] &&  str[*i] == quote)
		*i += 1;
}

char	*get_next_str(char *original, int *i)
{
	int	start = *i;

	if (!original[*i])
		return (NULL);
	while (original[*i])
	{
		if (original[*i] == '\'' || original[*i] == '\"')
		{
			skip_quote(original, i, original[*i]);
			continue ;
		}
		*i += 1;
		if (ft_isspace(original[*i]))
			break ;
	}
	return (ft_substr(original, start, *i - start));
}

void	split_and_add(char *to_split, char ***to_add)
{
	int	i;
	char	*str;
	i = 0;
	str = get_next_str(to_split, &i);
	while (str)
	{
		add_to_array(to_add, str);
		free(str);
		str = get_next_str(to_split, &i);
	}
}

void	expand_cmd(char **cmd, t_env **env, int stash_status)
{
	int		i;
	t_var	*keys;
	char	*new_cmd;
	char	**new = NULL;

	if (!cmd || !*cmd)
		return ;
	i = 0;
	while (cmd[i]) // *Necessary first , the possible next
	{
			new_cmd = expand_vars(&keys, &cmd[i], env,stash_status);// ? all the problems start from here
			// free(cmd[i]);
			// cmd[i] = new_cmd;
			// free(cmd[i]);// cmd[i] = ft_strdup(new_cmd); //  shit that amine changed are from here look it up
			if(keys && !is_empty_values(keys)) // Ayoub changed a lot of stuff
			{
				update_cmd(cmd[i], &keys, &new_cmd); // ! double free becuase keys
				// free(cmd[i]);
				// cmd[i] = new_cmd;
				// free_keys(&keys);
			}
			split_and_add(new_cmd, &new);
			// free(cmd[i]);
			// expand_quotes(old_cmd, alloc_len, &new_cmd);
		i++;
	}
	// free_cmd(*cmd);
	// *cmd = new;
}
