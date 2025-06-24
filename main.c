/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/24 17:54:21 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

/**
*
*/
t_token *find_PIPE(t_token *head, int nav_flag)
{
	t_token *current;

	if (!head)
		return printf("This is not supposed to happen.\n"), NULL;
	current = head;
	if(nav_flag)
	{
		while(current && current->next && current->next->position != -1)
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
 * @brief Creates a subtree if a Pipe is found in tokens
 * @param ast root node
 * @param tokens Tokenizer Tokens
 */
void create_subtree(t_tree **ast, t_token **tokens, int flag)
{
	int count;
	t_token *pipe_token;

	if (!tokens || !*tokens)
		return ;
	pipe_token = find_PIPE(*tokens, flag);
	if (pipe_token && pipe_token->type == TOKEN_PIPE)
	{
		*ast = create_block(&pipe_token, 1, block_identifier(pipe_token));
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
		if(flag)
			refresh_block(tokens);
		count = sub_block_arg_counter(*tokens);
		*ast = create_block(tokens, count, block_identifier(*tokens));
	}
}
/**
 * @brief Creates a subtree if a Pipe is found in tokens
 * @param ast root node
 * @param tokens Tokenizer Tokens
 */
t_token *find_and_or(t_token *head, int nav_flag)
{
	t_token *current;

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
 * @brief Creates a Tree
 * @param ast Root node
 * @param tokens Tokenizer Tokens
 * @param flag Navigation flag for search
 */
void create_tree(t_tree **ast, t_token **tokens ,int flag)
{
	t_token *and_or;

	if (!tokens || !*tokens)
		return ;
	and_or = find_and_or(*tokens, flag);
	if (and_or && (and_or->type == TOKEN_AND || and_or->type == TOKEN_OR))
	{
		printf("creating a { %s } block\n", and_or->value);
		*ast = create_block(&and_or, 1, block_identifier(and_or));
		and_or->position = -1;
		if (and_or->next)
			create_tree(&((*ast)->right), &and_or->next, 0);
		if (and_or->prev)
			create_tree(&((*ast)->left), &and_or->prev, 0);
	}
	else
	{
		if (flag)
			refresh_block(tokens);
		// printf(BLU "no more {||/&&} found ,Checking for pipes!!!\n" RESET);
		create_subtree(ast, tokens, 1);
	}
}

void f()
{
	system("leaks -q -- minishell");
}




int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	t_stash stash;

	// atexit(f);
	(void)argc, (void)argv;
	rl_catch_signals = 0;
	stash.status = 0;
	stash.heredoc_interrupted = 0;
	init_shell(&shell);
	build_env(&shell.env_list, envp);
	while (1)
	{
		g_sigint_received = 0; // Reset flag at the start of each loop
        stash.heredoc_interrupted = 0;
		setup_signals_prompt(); // Setup signals for the main prompt
		disable_echoctl(&stash);
		shell.line = readline("L33tShell-N.Y$ ");
		add_history(shell.line);
		if (!shell.line)
		{
			free_tokens(&shell.tokens);
			free_all_tracked();
			write(1, "exit\n", 5);
			printf("%d\n", stash.status);
			exit(stash.status);
		}
		if (!shell.line || ft_str_isspace(shell.line) || !lexer(&shell, 0) || !parser(shell))
		{
			free(shell.line);
			free_tokens(&shell.tokens);
			continue;
		}
		// visualize_tokens(shell.tokens);
		create_tree(&shell.ast, &shell.tokens, 1);
		// visualize_ast_tree(shell.ast);
		// print_tree(shell.ast);
		check_heredoc_limit(shell.ast);
		setup_signals_heredoc();
		manage_heredocs(shell.ast, &stash);
		if (!stash.heredoc_interrupted)
			execute_ast(shell.ast, &shell.env_list, &stash);
		else
		{
			clear_memory(&shell);
			continue;
		}
		if (ft_strnstr(shell.line, "leaks", ft_strlen(shell.line)))
			break;
		clear_memory(&shell);
	}
	clear_memory(&shell);
	return (0);
}
