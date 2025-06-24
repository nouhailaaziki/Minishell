/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:05:19 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/24 08:31:57 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

//

/// @brief Ctrl+C: Show a new prompt on a new line | Ctrl+D: in main, it exit the program | ctrl+\: do nothing
/// @paragraph it work with Ctrl+C: Show a new prompt on a new line,
void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);                 // Clears the current input line (uses readline)
	rl_on_new_line();                       // Moves to a new line internally
	rl_redisplay();                         // Shows the prompt again
}
 /**
 * @brief It configures how the parent process handles signals
 */
void	setup_signals_parent(void)
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
/**
 * @brief It sets the default behavior for signals in the child process
*/
void	setup_signals_child(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}



