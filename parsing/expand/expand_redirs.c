/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 06:13:39 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/23 18:12:17 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	expand_redirs(t_tree *ast, t_env **env, t_stash *stash, int stash_status)
{
	t_redir	*current;
	char	*tmp;
	char	*copy;

	current = ast->redirs;
	while (current)
	{
		if (current->type != REDIR_HEREDOC)
		{
			copy = ft_strdup(current->file);
			tmp = expand_vars(&current->file, env, stash_status, 0);
			// expand_quotes(&tmp);
			if (!ft_strcmp(tmp, "") || multi_str_included(tmp))
			{
				current->is_ambiguous = 1;
				current->file = ft_strdup(copy);
				free(tmp);
			}
			else
				current->file = tmp;
			free(copy);
		}
		current = current->next;
	}
	rebuild_redirs(ast, stash);
}

char	**redirs_to_arr(t_redir **head, size_t count)
{
	char	**redir_arr;
	t_redir	*current;

	if (!head || !*head)
		return (NULL);
	redir_arr = ft_calloc(count, sizeof(char *));
	if (!redir_arr)
		return (NULL);
	current = *head;
	count = 0;
	while (current)
	{
		redir_arr[count++] = ft_strdup(current->file);
		current = current->next;
	}
	return (redir_arr);
}

void	arr_to_redirs(t_redir *redirs, char **redir_arr)
{
	t_redir *current;
	int	i;
	current = redirs;

	i = 0;
	while (current)
	{
		free(current->file);
		current->file = ft_strdup(redir_arr[i++]);
		if (!ft_strcmp(current->file, "") || multi_str_included(current->file))
			current->is_ambiguous = 1;
		current = current->next;
	}
}
void rebuild_redirs(t_tree *ast, t_stash *stash)
{
	char	**redir_arr;
	t_redir	*current;
	size_t	count;

	if (!ast)
		return ;
	count = 0;
	current = ast->redirs;
	while(current)
	{
		count++;
		current = current->next;
	}
	redir_arr = redirs_to_arr(&ast->redirs, count);
	if(!redir_arr)
		return ;
	check_for_wildcards(ast,stash);
	arr_to_redirs(ast->redirs,redir_arr);
}







void	mask_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
		{
			if (str[i] == '\'')
				str[i] = 3;
			else
				str[i] = 4;
		}
		i++;
	}
}

void	unmask_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 3 || str[i] == 4)
		{
			if (str[i] == 3)
				str[i] = '\'';
			else
				str[i] = '"';
		}
		i++;
	}
}

void	expand_heredoc(t_redir **head)
{
	t_redir	*current;
	t_var	*keys;

	keys = NULL;
	current = *head;
	while (current)
	{
		if (current->type == REDIR_HEREDOC)
			current->flag = expand_quotes(&current->file);
		current = current->next;
	}
}

void	expand_keys_heredoc(t_var **keys, t_env **env, int stash_status, \
int *total_len)
{
	t_var	*current;
	int		keys_len;
	int		values_len;

	if (!keys || !*keys)
		return ;
	keys_len = 0;
	values_len = 0;
	current = *keys;
	while (current)
	{
		keys_len += current->key_len;
		expand_a_key(current, env, stash_status);
		current->value_len = ft_strlen(current->value);
		values_len += current->value_len;
		current = current->next;
	}
	*total_len = values_len - keys_len;
}
