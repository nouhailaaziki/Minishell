/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/18 13:20:17 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

void	clear_memory(t_shell *shell)
{
	if (shell->ast)
		free_tree(&shell->ast);
	if (shell->tokens)
		free_tokens(&shell->tokens);
	free(shell->line);
	shell->line = NULL;
}

int	init_shell(t_shell *shell)
{
	char	*tmp;
	char	*error;

	tmp = getcwd(0, 0);
	if (!isatty(0) || !isatty(1) || !tmp)
	{
		error = ft_strdup("L33tShell: input is not a terminal\n");
		if (!error)
			return (perror("malloc"), 1);
		write(2, error, ft_strlen(error));
		return (1);
	}
	free (tmp);
	display_intro();
	shell->env_list = NULL;
	shell->stash.status = 0;
	shell->stash.heredoc_interrupted = 0;
	shell->line = NULL;
	shell->tokens = NULL;
	shell->current = NULL;
	shell->ast = NULL;
	return (0);
}

void	init_loop_data(t_stash *stash)
{
	stash->is_parent_flag = 0;
	g_sigint_received = 0;
	stash->heredoc_interrupted = 0;
	stash->exit_flag = 0;
	stash->fork_failed = 0;
	setup_signals_prompt();
	disable_echoctl(stash);
}

int	process_input(t_shell *shell)
{
	if (ft_str_isspace(shell->line) || !lexer(shell) || !parser(shell))
	{
		free_tokens(&shell->tokens);
		return (0);
	}
	create_one_tree(&shell->ast, &shell->tokens);
	check_heredoc_limit(shell, shell->ast);
	return (1);
}

void	execute_cmds(t_shell *shell, t_stash *stash)
{
	int	required_forks;

	setup_signals_heredoc();
	manage_heredocs(shell->ast, stash);
	required_forks = count_required_forks(shell->ast);
	if (required_forks > 0 && perform_dry_run_fork_test(required_forks, stash))
	{
		ft_putendl_fd("L33tShell: fork failed: \
Resource temporarily unavailable", 2);
		stash->status = 1;
		return ;
	}
	if (!stash->heredoc_interrupted && !stash->fork_failed)
		execute_ast(shell->ast, &shell->env_list, stash);
	else
		return ;
	restore_terminal(stash);
}

void	close_fd()
{
	int	i;

	i = 3;
	while (i < OPEN_MAX)
		close(i++);	
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc, (void)argv;
	if (init_shell(&shell))
		return (1);
	build_env(&shell.env_list, envp, &shell.stash);
	while (1)
	{
		init_loop_data(&shell.stash);
		shell.line = readline("L33tShell-N.Y$ ");
		if (g_sigint_received)
			shell.stash.status = 1;
		add_history(shell.line);
		if (!shell.line)
		{
			write(1, "exit\n", 5);
			(free_tokens(&shell.tokens), free_all_tracked());
			exit(shell.stash.status);
		}
		if (process_input(&shell))
			execute_cmds(&shell, &shell.stash);
		clear_memory(&shell);
		close_fd();
	}
	return (0);
}
