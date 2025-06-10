/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/10 16:53:06 by yrhandou         ###   ########.fr       */
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

t_token *find_and_or(t_token **head)
{
	t_token *current;

	current = *head;
	while (current->next)
		current = current->next;
	while (current)
	{
		if (current->type == TOKEN_AND || current->type == TOKEN_OR)
			return current;
		current = current->prev;
	}
	printf("NO or/and FOUND\n");
	return NULL;
}

void create_one_tree(t_token **head, t_tree **ast)
{
	t_token *current;
	t_tree *tree;
	int count;

	tree = *ast;
	current = *head;
	current = find_and_or(&current);
	if (current)
	{
		tree = create_block(&current, 1, block_identifier(&current));
		current = current->next;
		count = block_arg_counter(&current);
		tree->right = create_block(&current, count, block_identifier(&current));
		reset_tokens(&current);
		current = *head;
		count = block_arg_counter(&current);
		tree->left = create_block(&current, count, block_identifier(&current));
		puts(BLU "head");
		print_tree(tree);
		print_tokens(head);
	}
	else
	{
		// reset_tokens(&current);
		current = *head;
		count = block_arg_counter(&current);
		tree = create_block(&current, count, block_identifier(&current));
		puts(BLU "head");
		print_tree(tree);
	}
}




int main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	t_token	*tokens, *current;
	t_tree	*ast;
	char	*line;
	int		count;

	(void)argc, (void)argv;
	tokens = NULL;
	7889 && (env_list = NULL, tokens = NULL, ast = NULL);
	display_intro();
	build_env(&env_list, envp);
	while (1)
	{
		line = readline(PINK BOLD "╰┈➤ L33tShell-N.Y ✗ " RESET);
		// line = ft_strdup("ls ");
		add_history(line);
		if (!line || !lexer(&tokens, line) || !parser(&tokens))
			continue;
		create_one_tree(&tokens,&ast);
		// executor(ast, &env_list);
		free_tokens(&tokens);
		free(line);
	}
	return (0);
}
