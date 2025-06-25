/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_tree_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:16:33 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/25 21:32:43 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

/**
 * @brief looks if a parentheses is found in tokens
 * @param head Head of tokens list
 * @param nav_flag Navigation flag for search
 */
t_token *find_Parentheses(t_token *head, int nav_flag)
{
	t_token *current;

	if (!head)
		return printf("This is not supposed to happen.\n"), NULL;
	current = head;
	if (nav_flag)
	{
		while (current && current->next)
			current = current->next;
	}
	while (current && current->position != -1)
	{
		if (current->type == TOKEN_PAREN_LEFT)
			return (current);
		current = current->prev;
	}
	return (NULL);
}
/**
 * @brief looks if a {&& , ||} is found in tokens
 * @param head Head of tokens list
 * @param nav_flag Navigation flag for search
 */
t_token *find_and_or(t_token *head, int nav_flag)
{
	t_token *current;
	int in_parenth;

	in_parenth = 0;
	if (!head)
		return printf("This is not supposed to happen.\n"), NULL;
	if (current->type == TOKEN_PAREN_RIGHT || current->type == TOKEN_PAREN_LEFT)
		in_parenth = 1;
	current = head;
	if (nav_flag && !in_parenth)
	{
		while (current && current->next)
			current = current->next;
	}
	while (current && current->prev && current->position != -1 )
		{
			if (current->type == TOKEN_AND || current->type == TOKEN_OR)
				return (current);
			current = current->prev;
		}
	return (NULL);
}
/**
 * @brief looks if a Pipe is found in tokens
 * @param head Head of tokens list
 * @param nav_flag Navigation flag for search
 */
t_token *find_PIPE(t_token *head, int nav_flag)
{
	t_token *current;

	if (!head)
		return printf("This is not supposed to happen.\n"), NULL;
	current = head;
	if (nav_flag)
	{
		while (current && current->next && current->next->position != -1)
			current = current->next;
	}
	while (current && current->prev && current->position != -1)
	{
		if (current->type == TOKEN_PIPE)
			return (current);
		current = current->prev;
	}
	return (NULL);
}
void refresh_block(t_token **head)
{
	while (*head && (*head)->prev && (*head)->prev->type != TOKEN_PIPE && (*head)->prev->type != TOKEN_AND && (*head)->prev->type != TOKEN_OR)
		*head = (*head)->prev;
}

/**
 * @brief Creates a subtree with a pipe as the root node if a Pipe is found in tokens
 * @param ast Root node
 * @param tokens Tokenizer Tokens
 * @param flag Navigation flag for search
 */
void create_subtree(t_tree **ast, t_token **tokens, int flag)
{
	t_token *pipe_token;

	if (!tokens || !*tokens)
		return;
	pipe_token = find_PIPE(*tokens, flag);
	if (pipe_token && pipe_token->type == TOKEN_PIPE)
	{
		*ast = create_block(&pipe_token, 1, block_identifier(pipe_token));
		// printf("Created a Pipe Node\n");
		pipe_token->position = -1;
		if (pipe_token->next)
			create_subtree(&(*ast)->right, &(pipe_token->next), 1);
		if (pipe_token->prev)
		{
			refresh_block(&pipe_token->prev);
			create_subtree(&(*ast)->left, &(pipe_token->prev), 0);
		}
	}
	else
	{
		printf("Checking for parentheses \n");
		create_pseudotree(ast, tokens, flag);
		// if (flag)
		// 	refresh_block(tokens);
		// *ast = create_block(tokens, sub_block_arg_counter(*tokens), block_identifier(*tokens));
	}
}

/**
 * @brief Creates a Tree
 * @param ast Root node
 * @param tokens Tokenizer Tokens
 * @param flag Navigation flag for search
 */
void create_one_tree(t_tree **ast, t_token **tokens, int flag)
{
	t_token *and_or;

	if (!tokens || !*tokens)
		return;
	and_or = find_and_or(*tokens, flag);
	if (and_or && (and_or->type == TOKEN_AND || and_or->type == TOKEN_OR))
	{
		// printf("creating a { %s } block\n", and_or->value);
		*ast = create_block(&and_or, 1, block_identifier(and_or));
		and_or->position = -1;
		if (and_or->next)
			create_subtree(&((*ast)->right), &and_or->next, 1);
		if (and_or->prev)
			create_one_tree(&((*ast)->left), &and_or->prev, 0);
	}
	else
	{
		// printf(BLU "no more {||/&&} found ,Checking for pipes!!!\n" RESET);
		create_subtree(ast, tokens, 1);
	}
}
