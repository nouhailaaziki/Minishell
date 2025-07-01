/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_misc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:37:17 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/01 09:42:41 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

t_redir	*redir_maker(t_token **data)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->fd = -1;
	redir->fd_rd = -1;
	redir->fd_wr = -1;
	redir->flag = 0;
	(*data)->position = -1;
	if ((*data)->next)
	{
		redir->file = ft_strdup((*data)->next->value);
		(*data)->next->position = -1;
		if (!redir->file)
			return (printf("This is not supposed to happen.\n"), NULL);
	}
	// redir->index = 0;
	redir->type = (*data)->type;
	redir->next = (NULL);
	return (redir);
}

void	link_redir(t_redir **head, t_redir *new_redir)
{
	t_redir	*tmp;

	tmp = *head;
	if (!*head)
	{
		*head = new_redir;
		new_redir->next = NULL;
		// new_redir->index = 0;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
	// new_redir->index = tmp->index + 1;
	new_redir->next = NULL;
}

t_redir	*redir_list_maker(t_token **head)
{
	t_token	*tmp;
	t_redir	*redir_list;

	redir_list = NULL;
	if (!head || !*head)
	{
		printf("This is not supposed to happen.\n");
		return (NULL);
	}
	tmp = *head;
	while (tmp && tmp->type != TOKEN_AND && tmp->type != TOKEN_OR && \
		tmp->type != TOKEN_PIPE && \
		tmp->type != TOKEN_PAREN_LEFT && tmp->type != TOKEN_PAREN_RIGHT)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || \
			tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
			link_redir(&redir_list, redir_maker(&tmp));
		tmp = tmp->next;
	}
	return (redir_list);
}
