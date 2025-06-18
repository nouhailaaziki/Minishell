/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/18 11:32:35 by yrhandou         ###   ########.fr       */
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

void reset_tokens(t_token **head)
{

	while ((*head)->position > 0)
		*head = (*head)->prev;
}

t_token *find_and_or(t_token **head, int nav_flag)
{
	t_token *current;

	current = *head;
	if (nav_flag == 0)
	{
		while (current->next)
			current = current->next;
	}
	while (current && current->prev && current->position != -1)
	{
		if (current->type == TOKEN_AND || current->type == TOKEN_OR)
			return (current);
		current = current->prev;
	}
	return (current);
}

t_token *find_PIPE(t_token *head)
{
	t_token *current;

	if (!head)
		return printf("This is not supposed to happen.\n"), NULL;
	current = head;
	while (current && current->next && current->position != -1)
	{
		if (current->type == TOKEN_PIPE)
			return (current);
		current = current->next;
	}
	return (NULL);
}
/**
 * @brief Creates a subtree if a Pipe is found in tokens
 * @param ast root node
 * @param tokens Tokenizer Tokens
 */

void create_subtree(t_tree **ast, t_token **tokens)
{
	int count;
	t_token *pipe_token;

	if (!tokens || !*tokens)
		return;
	pipe_token = find_PIPE(*tokens);
	if (pipe_token && pipe_token->type == TOKEN_PIPE)
	{
		*ast = create_block(&pipe_token, 1, block_identifier(pipe_token));
		pipe_token->position = -1;
		printf("Created a Pipe Node\n");
		if (pipe_token->prev)
			create_subtree(&(*ast)->left, &(pipe_token->prev));
		if (pipe_token->next)
			create_subtree(&(*ast)->right, &(pipe_token->next));
	}
	else
	{
		count = sub_block_arg_counter(*tokens);
		*ast = create_block(tokens, count, block_identifier(*tokens));
		// while (pipe_token && pipe_token->type != TOKEN_PIPE && pipe_token->type != TOKEN_AND && pipe_token->type != TOKEN_OR)
		// {
		// 	pipe_token->position = -1;
		// 	pipe_token = pipe_token->next;
		// }
	}
}
/**
 * * Recursion: look for and_or
 * * 	create the block for the op and th command on its right.
 * *  call this function but the result would be put to the left
 */
void create_one_tree(t_tree **ast, t_token **tokens)
{
	t_token *current;
	int count;

	if (!tokens || !*tokens)
		return;
	current = *tokens;
	current = find_and_or(&current, 0);
	if (current->type == TOKEN_AND || current->type == TOKEN_OR)
	{
		printf("creating a block\n");
		*ast = create_block(&current, 1, block_identifier(current));
		create_subtree(&((*ast)->right), &current->next);
		current->position = -1;
		create_one_tree(&((*ast)->left), &current->prev);
	}
	else if (current->type == TOKEN_PIPE)
	{
		create_subtree(ast, tokens);
	}
	else
	{
		printf(BLU "no more {||/&&} found ,creating one final node!!!\n" RESET);
		current = *tokens;
		count = block_arg_counter(current);
		(*ast) = create_block(&current, count, block_identifier(current));

		// free_tokens(&current);
	}
}

void f()
{
	system("leaks -q -- minishell");
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	atexit(f);
	(void)argc, (void)argv;
	display_intro();
	init_shell(&shell);
	build_env(&shell.env_list, envp);
	while (1)
	{
		shell.line = readline(PINK BOLD "╰┈➤ L33tShell-N.Y ✗ " RESET);
		// shell.line = ft_strdup("make ");
		add_history(shell.line);
		if (!shell.line || ft_str_isspace(shell.line) || !lexer(&shell, 0) || !parser(shell))
		{
			free(shell.line);
			free_tokens(&shell.tokens);
			continue;
		}
		visualize_tokens(shell.tokens);
		create_subtree(&shell.ast, &shell.tokens);
		visualize_ast_tree(shell.ast);
		// print_tree(shell.ast);
		// executor(shell.ast, &shell.env_list);
		if (ft_strnstr(shell.line, "leaks", ft_strlen(shell.line)))
			break;
		free(shell.line);
		clear_memory(&shell);
	}
	free(shell.line);
	clear_memory(&shell);
	return (0);
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
