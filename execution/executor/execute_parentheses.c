/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parentheses.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:37:16 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/24 17:56:39 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	execute_parentheses(t_tree *ast, t_env **env, t_stash *stash)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), 1);
	if (pid == 0)
	{
		exit_status = execute_ast(ast->left, env, stash);
		exit(exit_status);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
