/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:47:01 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/22 10:54:59 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

// int	execute_pipe(t_tree *ast, t_redir *redirs, t_env **env_list, t_stash *stash)
// {
// 	int 	pipes[2];
// 	t_tree	*tmp;
// 	pid_t	r_pid;
// 	pid_t	w_pid;

// 	if (pipe(pipes) == -1)
// 		return (perror("pipe"), 1);
// 	w_pid = fork(); // Child 1: write to pipe
// 	if (w_pid == -1)
// 	return (perror("fork"), 1);
// 	if (!w_pid)
// 	{
// 		dup2(pipes[1], STDOUT_FILENO);
// 		(close(pipes[0]), close(pipes[1]));
// 		tmp = ast->left;
// 		execute_command(tmp->cmd, redirs, env_list, stash);
// 		exit(1);
// 	}
// 	r_pid = fork(); // Child 2: read from pipe
// 	if (r_pid == -1)
// 		return (perror("fork"), 1);
// 	if (!r_pid)
// 	{
// 		dup2(pipes[0], STDIN_FILENO);
// 		(close(pipes[1]), close(pipes[0]));
// 		tmp = ast->right;
// 		execute_command(tmp->cmd, redirs, env_list, stash);
// 		exit(1);
// 	}
// 	(close(pipes[0]), close(pipes[1]));
// 	(waitpid(w_pid, NULL, 0), waitpid(r_pid, NULL, 0));
// 	return (0);
// }

int execute_pipe(t_tree *ast, t_env **env_list, t_stash *stash)
{
    int     pipes[2];
    t_tree  *left_cmd_node;
    t_tree  *right_cmd_node;
    pid_t   r_pid;
    pid_t   w_pid;

    if (pipe(pipes) == -1)
        return (perror("pipe"), 1);
    left_cmd_node = ast->left;
    w_pid = fork();
    if (w_pid == -1)
        return (perror("fork"), 1);
    if (w_pid == 0)
    {
        dup2(pipes[1], STDOUT_FILENO);
        (close(pipes[0]), close(pipes[1]));
        execute_command(left_cmd_node->cmd, left_cmd_node->redirs, env_list, stash);
        exit(1);
    }
    right_cmd_node = ast->right;
    r_pid = fork();
    if (r_pid == -1)
        return (perror("fork"), 1);
    if (r_pid == 0)
    {
        dup2(pipes[0], STDIN_FILENO);
        (close(pipes[1]), close(pipes[0]));
        execute_command(right_cmd_node->cmd, right_cmd_node->redirs, env_list, stash);
        exit(1);
    }
    (close(pipes[0]), close(pipes[1]));
    (waitpid(w_pid, NULL, 0), waitpid(r_pid, NULL, 0));
    return (0);
}