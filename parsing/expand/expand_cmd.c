/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:03:12 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/11 13:00:34 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void expand_a_key(t_var *current, t_env **env, int stash_status)
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

int is_empty_values(t_var *keys)
{
	while(keys)
	{
		if(keys->value != NULL)
			return 0;
		keys = keys->next;
	}
	return 1;
}

int skip_quoted_str(char *str, char quote)
{
	int i;

	i = 0;
 	while (str[i] && str[i] != quote)
		i++;
	if(str[i] == quote)
		i++;
	return (i);
}
int multi_str_included(char *new_cmd)
{
	int i;
	char quote;

	i = 0;
	quote = 0;
	while(new_cmd[i])
	{
		 if (ft_isquote(new_cmd[i]))
        {
            quote = new_cmd[i++];
			i += skip_quoted_str(&new_cmd[i], quote);
            if (ft_isspace(new_cmd[i]))
				return 1;
        }
		else
		{
			while(new_cmd[i] && !ft_isquote(new_cmd[i]))
			{
				if(ft_isspace(new_cmd[i]))
					return 1;
				i++;
			}
		}
	}
	return 0;
}



char	*expand_vars(char **old_cmd, t_env **env ,int stash_status)
{
	int		values_len;
	int		keys_len;
	int 	alloc_len;
	char	*new_cmd;
	t_var	*keys;

	keys_len = 0;
	values_len = 0;
	keys = NULL;
	find_all_keys(*old_cmd, &keys);
	expand_keys(&keys, env, stash_status, &keys_len, &values_len);
	alloc_len = ft_strlen(*old_cmd) +  values_len - keys_len;
	new_cmd = ft_calloc(alloc_len + 1, sizeof(char));
	if (!new_cmd)
		return (free(keys), *old_cmd);
	if (keys && !is_empty_values(keys))
	{
		update_cmd(*old_cmd, &keys, &new_cmd);
		free_keys(&keys);
	}
	else
		return free(new_cmd), *old_cmd;
	return (new_cmd);
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
}

void	skip_quote(char *str, int *i, char quote)
{
	while (str[*i] && str[*i] == quote)
		*i += 1;
	if (str[*i] &&  str[*i] == quote)
		*i += 1;
}

int	get_size(char **arr)
{
	int	s = 0;
	if (!arr)
		return 0;
	while (arr[s])
		s++;
	return (s);
}

char	**rebuild_cmd(t_token **list, size_t argc)
{
	char	**new_array;
	t_token	*current;
	int		i;

	if(!argc)
		return NULL;
	current = *list;
	new_array = ft_calloc(argc + 1, sizeof(char *));
	if (!new_array)
		return NULL;
	i = 0;
	while (current)
	{
		new_array[i++] = ft_strdup(current->value);
		current = current->next;
	}
	new_array[i] = NULL;
	return (new_array);
}

t_token	*get_next_str(char *original, int *i)
{
	int	start = *i;
	char quote;
	t_token *node;

	quote = 0;
	if (!original[*i])
		return (NULL);
	while (original[*i])
	{
		if (ft_isquote(original[*i]))
		{
			quote = original[(*i)++];
			*i += skip_quoted_str(original,quote);
			continue ;
		}
		*i += 1;
		if (ft_isspace(original[*i]))
			break ;
	}
	node = new_token(ft_substr(original, start, *i - start), TOKEN_WORD);
	return (node);
}

size_t filter_empty_nodes(t_token **head)
{
	t_token *current;
	size_t argc;

	if(!head)
		return 0;
	argc = 0;
	current = *head;
	while(current)
	{
		if(current->value && current->value[0] == '\0')
		{
			if(current->prev)
				current->prev->next = current->next;
			else
				*head = current->next;
			current = current->next;
		}
		else
		{
			argc++;
			current = current->next;
		}
	}
	return argc;
}

	// word_count = 0;
	// while(str[i])
	// 	word_count += word_counter(str[i++]);
	// new_cmd = ft_calloc(sizeof(char ),word_count);
void clean_tabs(char *str)
{
	int i;

	i=0;
	while(str[i])
	{
		if(!ft_isspace(str[i]))
			i++;
		else
			str[i++] = ' ';
	}
}
void	rebuild_list(char **str ,t_token **list)
{
	int i;
	int j;
	char **tmp;
	t_token *node;

	i = 0;
	j = 1;
	tmp = ft_split(*str, ' ');
	if(!tmp)
		return ;
	while (tmp)
	{
		i = 0;
		while (tmp[i])
		{
			clean_tabs(tmp[i]);
			node = new_token(ft_strdup(tmp[i]), TOKEN_WORD);
			link_token(list, node);
			i++;
		}
		free_cmd(tmp);
		tmp = ft_split(str[j++], ' ');
	}
}

void store_args(t_token **list, char **origin)
{
	int i;
	t_token *node;
	// char	**tmp;

	i = 0;
	while(origin[i])
	{
		if(multi_str_included(origin[i])) // ! make up your mind about this , replace the entire string or the entire 2d array
		{
			rebuild_list(origin, list);
			// if (tmp != origin)
			// 	free_cmd(tmp);
			// i = 0;
		}
		else
			node = new_token(ft_strdup(origin[i]), TOKEN_WORD); // ? what this do exactly
			// link_token(list,node);
		i++;
	}
}


void	handle_expand(char ***to_split)
{
	int	i;
	// t_token *str;
	t_token *list;
	size_t argc;

	if (!to_split || !**to_split )
		return ;
	list = NULL;
	i = 0;
	store_args(&list, *to_split);
	argc = filter_empty_nodes(&list);
	// str = get_next_str(**to_split, &i);
	*to_split = rebuild_cmd(&list, argc);
	free_tokens(&list);
	// while (str)
	// {

	// 	list = list->next;
	// 	str = get_next_str(**to_split, &i);
	// }

	// free_tokens(&list);
	// free_cmd(*to_split);
}

void	 expand_cmd(t_tree *ast, t_env **env, int stash_status)
{
	int		i;
	char	**current;

	current = (ast->cmd);
	if (!current || !*current || !**current)
		return ;
	i = 0;
	while (current && current[i]) // *Necessary first , the possible next
	{
			current[i] = expand_vars(&current[i], env, stash_status);
			if(!ft_strcmp(current[i], "") || multi_str_included(current[i])) // ? quotes are now removed at the wildcrads function
			{
				handle_expand(&current);
				ast->cmd = current;
				i = 0;
				continue;
			}
		i++;
	}
	// free_cmd(*cmd);
	// *cmd = new;
}
