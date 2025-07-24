/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:52:11 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/24 13:52:41 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	wild_check(char **tmp, t_stash *stash)
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
	return (free_cmd(redir_arr), 1);
}

void	expand_wild_redirs(t_tree *ast, t_stash *stash)
{
	t_redir	*current;

	current = ast->redirs;
	while (current)
	{
		if (current->type != REDIR_HEREDOC)
		{
			if (wild_check(&current->file, stash))
				current->is_ambiguous = 1;
		}
		current = current->next;
	}
}
