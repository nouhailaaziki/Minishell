/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/03 19:23:21 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

void print_tree(t_tree *tree, int arg_count)
{
	int i;

	i = 0;
	if (!tree)
		return;
	printf("Command is : ");
	while (i < arg_count)
		printf(BHGRN "<%s> " RESET, tree->cmd[i++]);
	printf("\n");
	printf("Argc : %zu\n", tree->argc);

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


void quote_expander(t_token **head)
{
	t_token *current;
	int position;
	int i;
	char quote;
	char *expanded_token;
	i = 0;
	position = 0;
	current = *head;
	while (current)
	{
		if (ft_strchr(current->value, '\"') == NULL && ft_strchr(current->value, '\'') == NULL)
		{
			current = current->next;
			continue;
		}
		expanded_token = ft_calloc(ft_strlen(current->value) + 1 , sizeof(char));
		if (!expanded_token)
			return free_tokens(head), ft_putendl_fd("MALLOC FAILURE", 2);
		while(current->value[i])
		{
		quote = ft_isquote(current->value[i]);
		if (quote != '\0')
		{
			i++;
			while (current->value[i] && current->value[i] != quote)
				expanded_token[position++] = current->value[i++];
			if (current->value[i] == quote)
				i++;
		}
		else
			expanded_token[position++] = current->value[i++];
		}
		if(expanded_token)
		{
			free(current->value);
			current->value = expanded_token;
		}
		current = current->next;
	}
}

void advanced_token_lexer(t_token **head)
{
	t_token *current;

	current = *head;
	while (current && current->next)
	{
		if(current->type == REDIR_HEREDOC || current->type == REDIR_IN)
			current->next->type = R_FILE;
		if (current->type== REDIR_OUT || current->type == REDIR_APPEND)
			current->next->type = R_FILE;
		if ((current->type == TOKEN_WORD || current->type ==TOKEN_ARG|| current->type == REDIR_IN || \
		 current->type == R_FILE) && current->next->type == TOKEN_WORD)
			current->next->type = TOKEN_ARG;
		current = current->next;
	}
}
int parser(t_token **head)
{
	t_token *current;

	current = *head;
	if (!current)
		return 0;
	if (ft_is_bonus_operator(current->value) || (current->type == TOKEN_PIPE))
		return ft_syntax_err(current->value, head);
	while (current)
	{
		if (ft_is_operator(current->value) && !current->next)
			return ft_syntax_err(current->value, head);
		if (ft_is_redir(current->value) && ft_isparentheses(current->next->value))
			return ft_syntax_err(current->value, head);
		current = current->next;
	}
	advanced_token_lexer(head);
	quote_expander(head);
	return 1;
}

void	print_redirs(t_redir *redir)
{
	while (redir)
	{
		printf("Redir type: ");
		if (redir->type == REDIR_IN)
			printf("REDIR_IN");
		else if (redir->type == REDIR_OUT)
			printf("REDIR_OUT");
		else if (redir->type == REDIR_APPEND)
			printf("REDIR_APPEND");
		else if (redir->type == REDIR_HEREDOC)
			printf("REDIR_HEREDOC");
		else
			printf("UNKNOWN");
		printf(", file: %s\n", redir->file);
		redir = redir->next;
	}
}
int block_arg_counter(t_token **head)
{
	t_token	*current;
	int		count;

	count = 0;
	current = *head;
	while (current)
	{
		if (current->type ==TOKEN_AND|| current->type == TOKEN_PIPE || current->type == TOKEN_OR)
			break;
		else if(current->type >= REDIR_IN)
		{
			current = current->next;
			continue;
		}
		count++;
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
t_tree *create_block(t_token **head, int count)
{
	t_tree *tree;
	int i;
	t_token *current;

	i = 0;
	tree = create_tree_node(count);
	if(!tree)
		return NULL;
	tree->redirs = redir_list_maker(head);
	current = *head;
	while (current && i < count)
	{
		if (current->type < REDIR_IN)
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
	int count;
	
	(void)argc, (void)argv;
	7889 && (env_list = NULL, tokens = NULL, ast = NULL);
	display_intro();
	build_env(&env_list, envp);
	while (1)
	{
		line = readline(PINK BOLD"╰┈➤ L33tShell-N.Y ✗ "RESET);
		if (!line || !lexer(&tokens, line) || !parser(&tokens))
		{
			add_history(line);
			continue;
		}
		count = block_arg_counter(&tokens);
		ast = create_block(&tokens,count);
		// print_tokens(&tokens);
		// print_tree(ast,count);
		executor(ast, &env_list);
		add_history(line);
		free_tokens(&tokens);
		free(line);
	}
	return (0);
}
