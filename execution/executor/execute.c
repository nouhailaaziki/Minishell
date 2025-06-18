/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/18 15:02:27 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	execute_ast(t_tree *ast, t_env **env)
{
	int	status;
	
	status = 1;
	if (!ast)
		return(status);
	if (ast->type == NODE_COMMAND)
		status = execute_command(ast->cmd, ast->redirs, env);
	else if (ast->type == NODE_PIPE)
		status = execute_pipe(ast, ast->redirs, env);
	else if (ast->type == NODE_AND)
	{
		status = execute_ast(ast->left, env);
		if (status == 0)
			return (status = execute_ast(ast->right, env));
		return (status);
	}
	else if (ast->type == NODE_OR)
	{
		status = execute_ast(ast->left, env);
		if (status != 0)
			return (execute_ast(ast->right, env));
		return (status);
	}
	return (status);
}