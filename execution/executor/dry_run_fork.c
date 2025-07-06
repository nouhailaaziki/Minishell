/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dry_run_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:06:29 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/06 20:54:45 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	count_required_forks(t_tree *ast)
{
	if (!ast)
		return (0);
	if (ast->type == NODE_COMMAND)
		return (1);
	else if (ast->type == NODE_PIPE)
		return (2 + count_required_forks(ast->left)
			+ count_required_forks(ast->right));
	else if (ast->type == NODE_PARENTHESES)
		return (1 + count_required_forks(ast->left));
	return (0);
}

int	perform_dry_run_fork_test(int required_forks, t_stash *stash)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < required_forks && !stash->fork_failed)
	{
		pid = fork();
		if (pid == -1)
			stash->fork_failed = 1;
		else if (pid == 0)
			exit(0);
		i++;
	}
	while (wait(NULL) > 0)
		;
	if (!stash->fork_failed)
		return (0);
	stash->fork_failed = 0;
	return (1);
}
