/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:41:43 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/28 11:17:06 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

t_token	*last_rp_token(t_token **head)
{
	t_token	*current;
	t_token	*r_parenth;

	if (!head)
		return (printf("This is not supposed to happen\n"), NULL);
	current = *head;
	r_parenth = NULL;
	while (current && current->position != -1)
	{
		if (current->type == TOKEN_PAREN_RIGHT)
			r_parenth = current;
		current = current->next;
	}
	if (r_parenth)
		r_parenth->position = -1;
	return (r_parenth);
}

t_redir	*p_redirs_maker(t_token **head)
{
	t_token	*tmp;
	t_redir	*redir_list;

	if (!head || !*head)
		return (printf("This is not supposed to happen.\n"), NULL);
	redir_list = NULL;
	tmp = last_rp_token(head);
	if (tmp && tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->type != TOKEN_AND && tmp->type != TOKEN_OR && \
		tmp->type != TOKEN_PIPE
		&& tmp->type != TOKEN_PAREN_LEFT && tmp->type != TOKEN_PAREN_RIGHT)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || \
			tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
		{
			link_redir(&redir_list, redir_maker(&tmp));
		}
		tmp = tmp->next;
	}
	return (redir_list);
}

/**
 * @brief looks if a parentheses is found in tokens
 * @param head Head of tokens list
 * @param nav_flag Navigation flag for search
 */
t_token	*find_first_lp(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (printf("This is not supposed to happen.\n"), NULL);
	current = tokens;
	while (current && current->position != -1)
	{
		if (current->type == TOKEN_PAREN_LEFT)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_tree	*create_p_block(t_token **head)
{
	t_tree	*p_block;
	int		i;

	i = 0;
	p_block = allocate_tree_node(NODE_PARENTHESES, 0);
	if (!p_block)
		return (NULL);
	p_block->redirs = p_redirs_maker(head);
	return (p_block);
}
