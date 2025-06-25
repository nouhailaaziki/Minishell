/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:30:50 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/23 11:31:48 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	disable_echoctl(t_stash *stash)
{
	struct termios	new_termios;

	tcgetattr(STDIN_FILENO, &stash->orig_termios);
	new_termios = stash->orig_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios);
}

void	restore_terminal(t_stash *stash)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &stash->orig_termios);
}
