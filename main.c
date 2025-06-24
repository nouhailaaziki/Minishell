/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/24 16:55:08 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

// ? i count the number of tokens until i stumble across a pipe/and/or.
// ! i check for redirections and fill them in a linked list
// * i fill inside the node the number of arguments
/*
	iterate the linked list and store the position of the last pao.
	create a node tree to its right and fill it with the last argument.

*/

void refresh_block(t_token **head)
{
	while (*head && (*head)->prev && (*head)->prev->type != TOKEN_PIPE)
		*head = (*head)->prev;
}

/**
 * @brief Creates a subtree with a pipe as the root node if a Pipe is found in tokens
 * @param head Root node
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
		while (current && current->next)
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
/**
 * @brief Creates a subtree with a pipe as the root node if a Pipe is found in tokens
 * @param ast Root node
 * @param tokens Tokenizer Tokens
 * @param flag Navigation flag for search
 */
int create_subtree(t_tree **ast, t_token **tokens, int flag)
{
	t_token *pipe_token;

	if (!tokens || !*tokens)
		return 0;
	pipe_token = find_PIPE(*tokens, flag);
	if (pipe_token && pipe_token->type == TOKEN_PIPE)
	{
		*ast = create_block(&pipe_token, 1, block_identifier(pipe_token));
		printf("Created a Pipe Node\n");
		pipe_token->position = -1;
		if (pipe_token->next)
			create_subtree(&(*ast)->right, &(pipe_token->next), 0);
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
	return 1;
}
t_token *find_and_or(t_token *head, int nav_flag)
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
	while (current && current->prev && current->position != -1)
	{
		if (current->type == TOKEN_AND || current->type == TOKEN_OR)
			return (current);
		current = current->prev;
	}
	return (NULL);
}
/**
 * * Recursion: look for and_or
 * * 	create the block for the op and th command on its right.
 * *  call this function but the result would be put to the left
 */
void create_one_tree(t_tree **ast, t_token **tokens, int flag)
{
	t_token *and_or;

	if (!tokens || !*tokens)
		return;
	and_or = find_and_or(*tokens, flag);
	if (and_or && (and_or->type == TOKEN_AND || and_or->type == TOKEN_OR))
	{
		printf("creating a { %s } block\n", and_or->value);
		*ast = create_block(&and_or, 1, block_identifier(and_or));
		and_or->position = -1;
		if (and_or->next)
			create_subtree(&((*ast)->right), &and_or->next, 0);
		if (and_or->prev)
			create_one_tree(&((*ast)->left), &and_or->prev, 0);
	}
	else
	{
		printf(BLU "no more {||/&&} found ,Checking for pipes!!!\n" RESET);
		create_subtree(ast, tokens, 1);
	}
}
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
	while (current && current->prev && current->position != -1)
	{
		if (current->type == TOKEN_PAREN_LEFT)
			return (current);
		current = current->prev;
	}
	return (NULL);
}
void create_pseudotree(t_tree **ast, t_token **tokens, int flag)
{
	t_token *parentheses;

	if (!tokens || !*tokens)
		return;
	parentheses = find_Parentheses(*tokens, TOKEN_PAREN_LEFT);
	if (parentheses)
	{
		*ast = create_block(&parentheses, 1, block_identifier(parentheses));
		printf("Created a Parentheses Node\n");
		if (parentheses->next)
			create_one_tree(&(*ast)->right, tokens, flag);
	}
	else
	{
		printf("No parentheses Found ! creating a simple node\n");
		if (flag)
			refresh_block(tokens);
		// create_pseudotree(ast, tokens, 0); // for parentheses check
		*ast = create_block(tokens, sub_block_arg_counter(*tokens), block_identifier(*tokens));
	}
}

void f()
{
	system("leaks -q -- minishell");
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	// atexit(f);
	(void)argc, (void)argv;
	display_intro();
	init_shell(&shell);
	build_env(&shell.env_list, envp);
	while (1)
	{
		// setup_signals_parent();
		shell.line = readline(PINK BOLD "╰┈➤ L33tShell-N.Y ✗ " RESET);
		if (!shell.line) // Ctrl+D should exit the shell using this.
		{
			free_tokens(&shell.tokens);
			free_all_tracked();
			write(1, "exit\n", 5);
			exit(0);
		}
		// shell.line = ft_strdup("make ");
		add_history(shell.line);
		if (!shell.line || ft_str_isspace(shell.line) || !lexer(&shell, 0) || !parser(shell))
		{
			free(shell.line);
			free_tokens(&shell.tokens);
			continue;
		}
		visualize_tokens(shell.tokens);
		create_one_tree(&shell.ast, &shell.tokens, 1);
		visualize_ast_tree(shell.ast);
		// print_tree(shell.ast);
		// execute_ast(shell.ast, &shell.env_list);
		if (ft_strnstr(shell.line, "leaks", ft_strlen(shell.line)))
			break;
		clear_memory(&shell);
	}
	return 0;
}
//?  // if (current->type != TOKEN_WORD)
//?  // {
//?  // 	tree->left = create_block(&current, 1, block_identifier(current));
//?  // 	count = block_arg_counter(&current->next);
//?  // 	tree->left->right = create_block(&current->next, count, block_identifier(current->next));
//?  // 	current = find_and_or(&current->prev, 1);
//?  // 	if (current->type != TOKEN_WORD)
//?  // 	{
//?  // 		printf("Reached The End of the demo\n");
//?  // 		exit(1);
//?  // 		return;
//?  // 	}
//?  // 		count = block_arg_counter(&current);
//?  // 		tree->left->left = create_block(&current, count, block_identifier(current));
//?  // }
//?  // else
//?  // {
//?  // 	count = block_arg_counter(&current);
//?  // 	tree->left = create_block(&current, count, block_identifier(current));
//?  // }
//?  // }
// else if((current = find_prev_PIPE(&current))->type == TOKEN_PIPE) //! look for why this keeps coming back to pipe problem with unctions not seperated ? or something , check its stop condition
// {
// 	tree = create_block(&current, 1, block_identifier(&current));
// 	count = sub_block_arg_counter(&current->next);
// 	tree->right = create_block(&current->next, count, block_identifier(current->next));
// 	current = find_prev_PIPE(&current->prev);
// 	if ( current->type == TOKEN_PIPE )
// 	{
// 		printf("EXTRA PIPE FOUND \n");
// 		// tree->left = create_block(&current, 1, block_identifier(&current));
// 		exit(0);
// 	}
// 	else
// 	{
// 		current = *head;
// 	}
// 	tree->left = create_block(&current, 1, block_identifier(&current));
// 	count = sub_block_arg_counter(&current);
// 	tree->left->right = create_block(&current->next, count, block_identifier(&current->next));
// }
// void create_subtree(t_tree **ast, t_token **tokens)
// {
// 	t_token *current;
// 	t_tree * sub_tree;
// 	int	count;
// 	t_token *pipe;
// 	count = 0;
// 	sub_tree = NULL;
// 	current = *tokens;
// 	pipe = find_prev_PIPE(current, 0);
// 	if(pipe->type == TOKEN_PIPE)
// 	{
// 		printf("Creating node for %s\n", pipe->value);
// 		sub_tree = create_block(&pipe, 1, block_identifier(current));
// 		pipe->position = -1;
// 		create_subtree(&sub_tree->right,&pipe->next);
// 		create_subtree(&sub_tree->left, &pipe->prev);
// 		// free_tokens(&current);
// 		// sub_tree->right = create_block(&current->next, count, block_identifier(current->next));
// 		// count = sub_block_arg_counter(current->prev);
// 		// sub_tree->left = create_block(&current->prev, count, block_identifier(current->prev));
// 	}
// 	else
// 	{
// 		printf("FINAL PIPE FUNCTION\n");
// 		count = block_arg_counter(pipe);
// 		sub_tree = create_block(&pipe, count, block_identifier(pipe));
// 		t_token *temp = pipe;
// 		while (temp && temp->type != TOKEN_PIPE)
// 		{
// 			temp->position = -1;
// 			temp = temp->next;
// 		}
// 		// ! YOU ARE HERE , the tree is filled with null because of something , i think in the find prev search conditions
// 	}
// 	current->position = -1;
// 		*ast = sub_tree;
// }
