/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/01 09:45:37 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "launchpad.h"

void init_shell(t_shell *shell)
{
	display_intro();
	shell->env_list = NULL;
	shell->line = NULL;
	shell->tokens = NULL;
	shell->current = NULL;
	shell->ast = NULL;
	shell->stash.status = 0;
	shell->stash.heredoc_interrupted = 0;
}
int main(int argc, char **argv, char **envp)
{
	t_shell shell;

//? HOW DO I LOOP OVER A TREE AND WHAT DO I WNAT TO DO TO THE EXPORT EXACTLY ? CHECK TLDRAW
int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	// atexit(f);
	(void)argc, (void)argv;
	stash.status = 0;
	stash.heredoc_interrupted = 0;
	init_shell(&shell);
	build_env(&shell.env_list, envp, &stash);
	// rl_catch_signals = 0;
	init_shell(&shell);
	build_env(&shell.env_list, envp, &shell.stash);
	while (1)
	{
		g_sigint_received = 0; // Reset flag at the start of each loop
		shell.stash.heredoc_interrupted = 0;
		setup_signals_prompt(); // Setup signals for the main prompt
		disable_echoctl(&shell.stash);
		shell.line = readline("L33tShell-N.Y$ ");
		restore_terminal(&stash);
		restore_terminal(&shell.stash);
		add_history(shell.line);
		if (!shell.line)
		{
			free_tokens(&shell.tokens);
			free_all_tracked();
			exit(shell.stash.status);
		}
		if (ft_str_isspace(shell.line) || !lexer(&shell) || !parser(&shell))
		{
			free(shell.line);
			free_tokens(&shell.tokens);
			continue ;
		}
		create_one_tree(&shell.ast, &shell.tokens);
		// visualize_tokens(shell.tokens);
		// visualize_ast_tree(shell.ast);
		// print_tree(shell.ast);
		check_heredoc_limit(&shell, shell.ast);
		setup_signals_heredoc();
		manage_heredocs(shell.ast, shell->stash);
		if (!stash.heredoc_interrupted)
			execute_ast(shell.ast, &shell.env_list, &stash);
		else
		{
			dprintf(2, "EXIT STATUS %d\n", stash.status);
			clear_memory(&shell);
			continue;
		}
		dprintf(2, "EXIT STATUS %d\n", stash.status);
	loop_exports(shell.tokens);
		// printf("first result : %s\n", rez ? rez->value : "NOTHING FOUND");
		clear_memory(&shell);

	}
	return (0);
}
