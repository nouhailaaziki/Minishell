/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_tree_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:16:33 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/27 09:09:40 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

void	create_pseudotree(t_tree **ast, t_token **tokens)
{
	t_token	*parentheses;

	if (!tokens || !*tokens)
		return ;
	refresh_tokens(tokens);
	parentheses = find_first_lp(*tokens);
	if (parentheses)
	{
		*ast = create_p_block(&parentheses);
		parentheses->position = -1;
		if (parentheses->next)
			create_one_tree(&(*ast)->left, &parentheses->next);
	}
	else
		*ast = create_block(tokens, count_cmd_args(*tokens), \
		block_identifier(*tokens));
}

t_token	*find_pipe(t_token *tokens)
{
	t_token	*current;
	t_token	*last_pipe;
	int		in_parenthese;

	if (!tokens)
		return (NULL);
	current = tokens;
	last_pipe = NULL;
	in_parenthese = 0;
	while (current)
	{
		if (current->type == TOKEN_PAREN_LEFT)
			in_parenthese++;
		if (current->type == TOKEN_PAREN_RIGHT)
			in_parenthese--;
		if (current->type == TOKEN_PIPE && current->position != -1 && \
			!in_parenthese)
			last_pipe = current;
		current = current->next;
	}
	return (last_pipe);
}

void	create_subtree(t_tree **ast, t_token **tokens)
{
	t_token	*last_pipe;

	if (!tokens || !*tokens)
		return ;
	refresh_tokens(tokens);
	last_pipe = find_pipe(*tokens);
	if (last_pipe && last_pipe->type == TOKEN_PIPE)
	{
		*ast = create_block(&last_pipe, 1, block_identifier(last_pipe));
		last_pipe->position = -1;
		if (last_pipe->next)
			create_pseudotree(&(*ast)->right, &(last_pipe->next));
		if (last_pipe->prev)
			create_subtree(&(*ast)->left, &(last_pipe->prev));
	}
	else
		create_pseudotree(ast, tokens);
}

t_token	*find_and_or(t_token *head)
{
	t_token	*current;
	t_token	*last_and_or;
	int		in_parenthese;

	if (!head)
		return (NULL);
	in_parenthese = 0;
	current = head;
	last_and_or = NULL;
	while (current && current->position != -1)
	{
		if (current->type == TOKEN_PAREN_LEFT)
			in_parenthese++;
		if (current->type == TOKEN_PAREN_RIGHT)
			in_parenthese--;
		if ((current->type == TOKEN_AND || current->type == TOKEN_OR) && \
		!in_parenthese)
			last_and_or = current;
		current = current->next;
	}
	return (last_and_or);
}

void	create_one_tree(t_tree **ast, t_token **tokens)
{
	t_token	*last_and_or;

	if (!tokens || !*tokens)
		return ;
	refresh_tokens(tokens);
	last_and_or = find_and_or(*tokens);
	if (last_and_or)
	{
		*ast = create_block(&last_and_or, 1, block_identifier(last_and_or));
		last_and_or->position = -1;
		if (last_and_or->next)
			create_subtree(&((*ast)->right), &last_and_or->next);
		if (last_and_or->prev)
			create_one_tree(&((*ast)->left), &last_and_or->prev);
	}
	else
		create_subtree(ast, tokens);
}
