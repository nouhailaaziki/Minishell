/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:03:12 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/20 09:38:51 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	update_cmd(char *origin, t_var **keys, char **destination, int heredoc)
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
			ft_copy_keys(&dest, current, heredoc);
			i += current->key_len;
			current = current->next;
		}
		else
			*dest++ = origin[i++];
	}
	*dest = '\0';
	*destination = tmp;
	free(origin);
}

void	handle_expand(char ***to_split)
{
	t_token	*list;
	size_t	argc;
	char	**new_cmd;

	if (!to_split || !**to_split)
		return ;
	list = NULL;
	argc = 0;
	store_args(&list, *to_split);
	filter_empty_nodes(&list, &argc);
	new_cmd = rebuild_cmd(&list, argc);
	free_cmd(*to_split);
	*to_split = new_cmd;
	free_tokens(&list);
}

int	multi_str_included(char *new_cmd)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (new_cmd[i])
	{
		if (ft_isquote(new_cmd[i]))
		{
			quote = new_cmd[i++];
			i += skip_quoted_str(&new_cmd[i], quote);
			if (new_cmd[i] == ' ' || new_cmd[i] == '\t' )
				return (1);
		}
		else
		{
			while (new_cmd[i] && !ft_isquote(new_cmd[i]))
			{
				if (new_cmd[i] == ' ' || new_cmd[i] == '\t' )
					return (1);
				i++;
			}
		}
	}
	return (0);
}

char	*expand_vars(char **old_cmd, t_env **env, int stash_status, int heredoc)
{
	int		total_len;
	int		alloc_len;
	char	*new_cmd;
	t_var	*keys;

	total_len = 0;
	keys = NULL;
	find_all_keys(*old_cmd, &keys);
	if (!heredoc)
		expand_keys(&keys, env, stash_status, &total_len);
	else
		expand_keys_heredoc(&keys, env, stash_status, &total_len);
	alloc_len = ft_strlen(*old_cmd) + total_len;
	new_cmd = ft_calloc(alloc_len + 1, sizeof(char));
	if (!new_cmd)
		return (free(keys), *old_cmd);
	if (keys && !is_empty_values(keys))
	{
		update_cmd(*old_cmd, &keys, &new_cmd, heredoc);
		free_keys(&keys);
	}
	else
		return (free(new_cmd), free_keys(&keys), *old_cmd);
	return (new_cmd);
}

void	expand_cmd(t_tree *ast, t_env **env, int stash_status)
{
	int		i;
	char	**current;

	current = ast->cmd;
	if (!current || !*current || !**current)
		return ;
	i = 0;
	while (current && current[i])
	{
		current[i] = expand_vars(&current[i], env, stash_status, 0);
		if (!ft_strcmp(current[i], "") || multi_str_included(current[i]))
		{
			handle_expand(&current);
			ast->cmd = current;
			i = 0;
			continue ;
		}
		i++;
	}
}
