/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/18 15:19:36 by noaziki          ###   ########.fr       */
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
	while((*head)->position > 0)
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
	while (current && current->prev)
	{
		if (current->type == TOKEN_AND || current->type == TOKEN_OR)
			return (current);
		current = current->prev;
	}
	return (current);
}

t_token *find_prev_PIPE(t_token *head, int nav_flag)
{
	t_token *current;

	current = head;
	if (nav_flag == 0)
	{
		while (current->next)
			current = current->next;
	}
	while (current && current->prev)
	{
		if (current->type == TOKEN_PIPE)
			return (current);
		current = current->prev;
	}
	return (current);
}



void create_one_tree(t_shell *shell)
{
	t_token	*current;
	t_tree	*tree;
	int		count;

	tree = (shell->ast);
	current = shell->tokens;
	current = find_and_or(&current,0);
	if (current->type == TOKEN_AND || current->type == TOKEN_OR)
	{
		tree = create_block(&current, 1, block_identifier(current));
		count = block_arg_counter(&current->next);
		tree->right = create_block(&current->next, count, block_identifier(current->next));
		current = find_and_or(&current->prev,1);
		if (current->type != TOKEN_WORD)
		{
			tree->left = create_block(&current, 1, block_identifier(current));
			count = block_arg_counter(&current->next);
			tree->left->right = create_block(&current->next, count, block_identifier(current->next));
			current = find_and_or(&current->prev, 1);
			if (current->type != TOKEN_WORD)
			{
				printf("Reached The End of the demo\n");
				exit(1);
				return;
			}
				count = block_arg_counter(&current);
				tree->left->left = create_block(&current, count, block_identifier(current));
		}
		else
		{
			count = block_arg_counter(&current);
			tree->left = create_block(&current, count, block_identifier(current));
		}
		}
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
	else
	{
		// printf(BLU"no or/and FOUND ,creating one node!!!\n"RESET);
		current = shell->tokens;
		count = block_arg_counter(&current);
		tree = create_block(&current, count, block_identifier(current));
	}
	
	shell->ast = tree;
	current = NULL;
}

void f()
{
	system("leaks -q -fullContent -- minishell");
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
		shell.line = readline(PINK BOLD "╰┈➤ L33tShell-N.Y ✗ " RESET);
		// shell.line = ft_strdup("ls > a ");
		add_history(shell.line);
		if (!shell.line || ft_str_isspace(shell.line) || !lexer(&shell, 0) || !parser(shell))
		{
			free(shell.line);
			continue;
		}
		create_one_tree(&shell);
		// visualize_ast_tree(shell.ast); // * FIX REDIR TYPE
		// print_tokens(&shell.tokens);
		// print_tree(shell.ast);
		execute_ast(shell.ast, &shell.env_list);
		 clear_memory(&shell);
		if(ft_strnstr(shell.line, "leaks", ft_strlen(shell.line)))
			break;
	}
	return (0);
}

