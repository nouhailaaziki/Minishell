/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/22 10:49:54 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	execute_ast(t_tree *ast, t_env **env, t_stash *stash)
{	
	stash->status = 1;
	if (!ast)
		return(stash->status);
	if (ast->type == NODE_COMMAND)
		stash->status = execute_command(ast->cmd, ast->redirs, env, stash);
	else if (ast->type == NODE_PIPE)
		stash->status = execute_pipe(ast, env, stash);
	else if (ast->type == NODE_AND)
	{
		stash->status = execute_ast(ast->left, env, stash);
		if (stash->status == 0)
			return (stash->status = execute_ast(ast->right, env, stash));
		return (stash->status);
	}
	else if (ast->type == NODE_OR)
	{
		stash->status = execute_ast(ast->left, env, stash);
		if (stash->status != 0)
			return (execute_ast(ast->right, env, stash));
		return (stash->status);
	}
	return (stash->status);
}