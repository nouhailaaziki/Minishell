/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:05:19 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/18 19:03:51 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

// Ctrl+C: Show a new prompt on a new line | Ctrl+D: in main, it exit the program | ctrl+\: do nothing

void	handle_sigint(int sig)              // it work with Ctrl+C: Show a new prompt on a new line
{
	(void)sig;                              // Ignores the parameter since we don’t use it
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);                 // Clears the current input line (uses readline)
	rl_on_new_line();                       // Moves to a new line internally
	rl_redisplay();                         // Shows the prompt again
}

void	setup_signals_parent(void)          // It configures how the parent process handles signals
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	setup_signals_child(void)           // It sets the default behavior for signals in the child process
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}



