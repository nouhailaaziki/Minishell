/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:28:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/05 19:10:33 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	setup_signals_heredoc(void)
{
	struct sigaction	sa_int;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = handle_sigint_heredoc;
	sigaction(SIGINT, &sa_int, NULL);
}

void	setup_signals_prompt(void)
{
	struct sigaction	sa_int;

	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = handle_sigint_prompt;
	sigaction(SIGINT, &sa_int, NULL);
}
