/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:47:01 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/24 08:21:25 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	execute_left_child(t_tree *ast, t_env **env_list, \
t_stash *stash, int *pipes)
{
	close(pipes[0]);
	dup2(pipes[1], STDOUT_FILENO);
	close(pipes[1]);
	execute_ast(ast->left, env_list, stash);
	exit(stash->status);
}

void	execute_right_child(t_tree *ast, t_env **env_list, \
t_stash *stash, int *pipes)
{
	close(pipes[1]);
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[0]);
	execute_ast(ast->right, env_list, stash);
	exit(stash->status);
}

int	wait_for_children(pid_t left_pid, pid_t right_pid, t_stash *stash)
{
	waitpid(left_pid, &stash->status, 0);
	waitpid(right_pid, &stash->status, 0);
	return (WEXITSTATUS(stash->status));
}

int	execute_pipe(t_tree *ast, t_env **env_list, t_stash *stash)
{
	pid_t	left_pid;
	pid_t	right_pid;
	int		pipes[2];

	if (pipe(pipes) == -1)
		return (perror("pipe"), 1);
	left_pid = fork();
	if (left_pid == -1)
		return (perror("fork"), 1);
	if (left_pid == 0)
		execute_left_child(ast, env_list, stash, pipes);
	right_pid = fork();
	if (right_pid == -1)
		return (perror("fork"), 1);
	if (right_pid == 0)
		execute_right_child(ast, env_list, stash, pipes);
	close(pipes[0]);
	close(pipes[1]);
	return (wait_for_children(left_pid, right_pid, stash));
}
