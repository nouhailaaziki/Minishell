/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/09 17:30:31 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

void print_tree(t_tree *tree)
{
	int	i;

	i = 0;
	if (!tree)
	{
		printf(BLU"EMPTY TREE\n"RESET);
		return;
	}
	printf("Command is : ");
	while (tree->cmd[i])
		printf(BHGRN "{%s} " RESET, tree->cmd[i++]);
	printf("\nArgc : %zu\n", tree->argc);

	if (tree->redirs)
	{
		printf(BLU "Redirs :");
		while (tree->redirs)
		{
			printf("{%zu}[%d][%s] , ",tree->redirs->index, tree->redirs->type, tree->redirs->file);
			tree->redirs = tree->redirs->next;
		}
		printf(RESET "}\n");
	}
}

int *block_arg_counter(t_token **head)
{
	t_token	*current;
	int		*count;

	count = ft_calloc(2, sizeof(int));
	current = *head;
	while (current)
	{
		if (current->type ==TOKEN_AND|| current->type == TOKEN_PIPE || current->type == TOKEN_OR)
			break;
		else if(current->type == TOKEN_REDIR)
		{
			count[1]++;
			current = current->next;
			continue;
		}
		count[0]++;
		current = current->next;
	}
	return count;
}
// void	print_ast(t_tree *node)
// {
// 	if (!node)
// 		return ;
// 	if (node->type == NODE_COMMAND)
// 	{
// 		printf("NODE_COMMAND: ");
// 		for (int i = 0; node->cmd && node->cmd[i]; i++)
// 			printf("%s ", node->cmd[i]);
// 		printf("\n");
// 		if (node->redirs)
// 		{
// 			printf("Redirections:\n");
// 			print_redirs(node->redirs);
// 		}
// 	}
// 	else if (node->type == NODE_PIPE)
// 	{
// 		printf("NODE_PIPE:\n");
// 		print_ast(node->left);
// 		print_ast(node->right);
// 	}
// }

// ? i count the number of tokens until i stumble across a pipe/and/or.
// ! i check for redirections and fill them in a linked list
// * i fill inside the node the number of arguments
/*
	iterate the linked list and store the position of the last pao.
	create a node tree to its right and fill it with the last argument.

*/


t_tree *create_block(t_token **head, int *count)
{
	t_tree *tree;
	int		i;
	t_token *current;

	i = 0;
	tree = create_tree_node(NODE_COMMAND, count);
	if(!tree)
		return NULL;
	tree->redirs = redir_list_maker(head,count[1]);
	current = *head;
	while (current && i < count[0])
	{
		if (current->type != TOKEN_REDIR)
			tree->cmd[i++] = ft_strdup(current->value);
		current = current->next;
	}
	tree->cmd[i] = NULL;
	return (tree);
}
int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	t_token	*tokens;
	t_tree	*ast;
	char	*line;
	int		*count;
	t_token * current;
	int I =0;

	current = tokens;
	(void)argc, (void)argv;
	7889 && (env_list = NULL, tokens = NULL, ast = NULL);
	display_intro();
	build_env(&env_list, envp);
	while (1)
	{
		line = readline(PINK BOLD"╰┈➤ L33tShell-N.Y ✗ "RESET);
		// line = ft_strdup("ls");
		add_history(line);
		if (!line || !lexer(&tokens, line) || !parser(&tokens))
			continue;
		// while (current && I < 3)
		// {
		count = block_arg_counter(&tokens);
		// 	if(!ast)
		// 		ast = create_block(&current,count);
		// 	else
		// 		ast-> = create_block(&current, count);
		// 	while(count >0)
		// 	{
			// 		count--;
			// 		current = current->next;
			// 	}
			// 	if(current->type == TOKEN_AND)

			// }
		ast->left = create_block(&tokens,count);
		ast = create_block(,1);
		print_tree(ast);
		print_tokens(&tokens);
		// executor(ast, &env_list);
		free_tokens(&tokens);
		free(line);
	}
	return (0);
}
