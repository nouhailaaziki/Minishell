/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:07:33 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/17 12:48:45 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	count_heredocs(t_redir *redir)
{
	t_redir	*current;
	int		counter;

	current = redir;
	counter = 0;
	while (current && current->type)
	{
		if (current->type == REDIR_HEREDOC)
			counter++;
		current = current->next;
	}
	return (counter);
}

void	manage_heredocs(t_tree *ast, t_stash *stash)
{
	if (!ast || stash->heredoc_interrupted)
		return ;
	if (ast->type == NODE_COMMAND)
	{
		expand_heredoc(&ast->redirs);
		if (count_heredocs(ast->redirs) > 0)
		{
			if (open_heredocs(ast->redirs, stash) != 0)
			{
				stash->status = 1;
				return ;
			}
		}
	}
	manage_heredocs(ast->left, stash);
	manage_heredocs(ast->right, stash);
}

void	check_heredoc_limit(t_shell *shell, t_tree *ast)
{
	int		counter;
	t_redir	*redir;

	counter = 0;
	if (shell->ast && shell->ast->type == NODE_COMMAND)
	{
		redir = shell->ast->redirs;
		while (redir && redir->type)
		{
			if (redir->type == REDIR_HEREDOC)
				counter++;
			redir = redir->next;
		}
	}
	if (counter > 16)
	{
		write(2, "L33tShell: maximum here-document count exceeded\n", 49);
		free_all_tracked();
		clear_memory(shell);
		exit(2);
	}
	if (ast->left)
		check_heredoc_limit(shell, ast->left);
	if (ast->right)
		check_heredoc_limit(shell, ast->right);
}
