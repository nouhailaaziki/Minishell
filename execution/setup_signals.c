/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:05:19 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/22 16:45:10 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

struct termios orig_termios;

void disable_echoctl(void)
{
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    new_termios = orig_termios;
    new_termios.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios);
}

void restore_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void handle_sigint_heredoc(int sig)
{
    (void)sig;
    g_sigint_received = 1;
}

void handle_sigint_prompt(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void setup_signals_prompt(void)
{
    struct sigaction sa_int;

    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sa_int.sa_handler = handle_sigint_prompt;
    sigaction(SIGINT, &sa_int, NULL);
}

void setup_signals_heredoc(void)
{
    struct sigaction sa_int;

    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sa_int.sa_handler = handle_sigint_heredoc;
    sigaction(SIGINT, &sa_int, NULL);
}
