/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 06:13:39 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/24 10:20:46 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int wild_check(char **tmp, t_stash *stash)
{
	char	**redir_arr;
	int		count;

	if (!ft_strchr(*tmp, '*'))
		return (0);
	redir_arr = ft_calloc(2, sizeof(char *));
	if (!redir_arr)
		return (0);
	redir_arr[0] = ft_strdup(*tmp);
	redir_arr[1] = NULL;
	check_for_wildcards(&redir_arr, stash);
	count = 0;
	while (redir_arr && redir_arr[count])
		count++;
	if (count == 1)
	{
		free(*tmp);
		*tmp = ft_strdup(redir_arr[0]);
		return (free_cmd(redir_arr), 0);
	}
	return (free_cmd(redir_arr),1);
}
void	expand_wild_redirs(t_tree *ast, t_stash *stash)
{
	t_redir	*current;


	current = ast->redirs;
	while (current)
	{
		if (current->type != REDIR_HEREDOC)
		{
			if (wild_check(&current->file, stash) )
				current->is_ambiguous = 1;
		}
		current = current->next;
	}
}

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
				free(tmp);
				current->file = ft_strdup(copy);
				current->is_ambiguous = 1;
			}
			else
				current->file = tmp;
			free(copy);
		}
		current = current->next;
	}
	expand_wild_redirs(ast,stash);
}

// char	**redir_to_arr(t_redir **head, size_t count)
// {
// 	char	**redir_arr;
// 	t_redir	*current;

// 	if (!head || !*head)
// 		return (NULL);
// 	redir_arr = ft_calloc(count + 1, sizeof(char *));
// 	if (!redir_arr)
// 		return (NULL);
// 	current = *head;
// 	count = 0;
// 	while (current)
// 	{
// 		redir_arr[count++] = ft_strdup(current->file);
// 		current = current->next;
// 	}
// 	redir_arr[count] = NULL;
// 	return (redir_arr);
// }

// void	arr_to_redirs(t_redir *redirs, char **redir_arr, int count)
// {
// 	t_redir *current;
// 	int	i;
// 	current = redirs;

// 	i = 0;
// 	while (current)
// 	{
// 		free(current->file);
// 		current->file = ft_strdup(redir_arr[i++]);
// 		if (!ft_strcmp(current->file, "") || multi_str_included(current->file))
// 			current->is_ambiguous = 1;
// 		current = current->next;
// 	}
// }
// void rebuild_redir(t_tree *ast, t_stash *stash)
// {
// 	char	**redir_arr;
// 	t_redir	*current;
// 	size_t	count;

// 	if (!ast)
// 		return ;
// 	count = 0;
// 	current = ast->redirs;
// 	while(current)
// 	{
// 		count++;
// 		current = current->next;
// 	}
// 	redir_arr = redir_to_arr(&ast->redirs, count);
// 	if(!redir_arr)
// 		return ;
// 	check_for_wildcards(&redir_arr,stash);
// 	arr_to_redirs(ast->redirs,redir_arr, count);
// 	free_cmd(redir_arr);
// }







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
