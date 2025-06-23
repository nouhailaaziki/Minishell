/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:47:01 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/23 08:36:43 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int execute_pipe(t_tree *ast, t_env **env_list, t_stash *stash)
{
    pid_t left_pid;
    pid_t right_pid;
    int pipes[2];
    
    if (pipe(pipes) == -1)
        return (perror("pipe"), 1);
    left_pid = fork();
    if (left_pid == -1)
        return (perror("fork"), 1);
    if (left_pid == 0)
    {
        close(pipes[0]);
        dup2(pipes[1], STDOUT_FILENO);
        close(pipes[1]);
        execute_command(ast->left->cmd, ast->left->redirs, env_list, stash);
        exit(stash->status);
    }
    right_pid = fork();
    if (right_pid == -1)
        return (perror("fork"), 1);
    if (right_pid == 0)
    {
        close(pipes[1]);
        dup2(pipes[0], STDIN_FILENO);
        close(pipes[0]);
        execute_command(ast->right->cmd, ast->right->redirs, env_list, stash);
        exit(stash->status);
    }
    (close(pipes[0]), close(pipes[1]));
    waitpid(left_pid, &stash->status, 0);
    waitpid(right_pid, &stash->status, 0);
    return (WEXITSTATUS(stash->status));
}
