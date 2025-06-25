/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/25 16:54:49 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

/**
 * @brief Creates a tree for content inside parentheses
 * @param ast Root node
 * @param tokens Tokenizer Tokens
 * @param flag Navigation flag for search
 */
void create_pseudotree(t_tree **ast, t_token **tokens, int flag)
{
	t_token *parentheses;

	if (!tokens || !*tokens)
		return;
	parentheses = find_Parentheses(*tokens, flag);
	if (parentheses)
	{
		*ast = create_block(&parentheses, 1, block_identifier(parentheses));
		parentheses->position = -1;
		printf("Created a Parentheses Node\n");
		if (parentheses->next)
			create_one_tree(&(*ast)->left, &parentheses->next, flag);
	}
	else
	{
		printf("No parentheses Found ! creating a simple node\n");
		// if (flag)
		// 	refresh_block(tokens);
		// create_pseudotree(ast, tokens, 0); // for parentheses check
		*ast = create_block(tokens, sub_block_arg_counter(*tokens), block_identifier(*tokens));
	}
}
// int create_p_block(t_token **head, int count, int type)
// {
// 	t_token * current;

// 	current = *head;
// 	while()
// 	return 1;
// }


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
		visualize_tokens(shell.tokens);
		create_one_tree(&shell.ast, &shell.tokens, 1);
		visualize_ast_tree(shell.ast);
		// print_tree(shell.ast);
		// check_heredoc_limit(&shell,shell.ast); // ? Changed the freeing to include clear memory.
		// setup_signals_heredoc();
		// manage_heredocs(shell.ast, &stash);
		// if (!stash.heredoc_interrupted)
		// 	execute_ast(shell.ast, &shell.env_list, &stash);
		// else
		// {
		// 	clear_memory(&shell);
		// 	continue;
		// }
		if (ft_strnstr(shell.line, "leaks", ft_strlen(shell.line)))
			break;
		clear_memory(&shell);
	}
	clear_memory(&shell);
	return (0);
}
